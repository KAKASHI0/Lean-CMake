#if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
#	set(NO_BOM_PATH_SUFFIX NoBOM CACHE STRING "The path suffix for generated No-BOM files in linux.")
#endif()

# Read a variable from cache. The default value in cache is "".
# When the value in cache is "", EMPTY_DEFAULT_VALUE is returned.
# Cache options: <VARIABLE_NAME>
# Global vars: <VARIABLE_NAME>
function(read_cache VARIABLE_NAME VARIABLE_TYPE EMPTY_DEFAULT_VALUE DOC_STRING)
	# Cache options
	set(${VARIABLE_NAME} "" CACHE ${VARIABLE_TYPE} ${DOC_STRING})
	# If empty, use default value
	if(NOT ${VARIABLE_NAME})
		set(${VARIABLE_NAME} ${EMPTY_DEFAULT_VALUE} PARENT_SCOPE)
	endif()
endfunction(read_cache)

# Add a system library definition
# Global vars: <LIBRARY_TARGET>_LIBRARIES
function(find_system_lib LIBRARY_TARGET)
	set(${LIBRARY_TARGET}_LIBRARIES ${ARGN} PARENT_SCOPE)
endfunction(find_system_lib)

# Add a external library definition
# Cache options: DEPENDENCIES_<LIBRARY_TARGET>_INCLUDE_DIR DEPENDENCIES_<LIBRARY_TARGET>_LIB_DIR DEPENDENCIES_<LIBRARY_TARGET>_LIBRARIES DEPENDENCIES_<LIBRARY_TARGET>_LIBRARIES_DEBUG
# Global vars: <LIBRARY_TARGET>_INCLUDE_DIR <LIBRARY_TARGET>_LIB_DIR <LIBRARY_TARGET>_LIBRARIES <LIBRARY_TARGET>_FOUND
function(find_external_lib LIBRARY_TARGET)
	# Output messages
	message(STATUS "Finding external lib: ${LIBRARY_TARGET}")

	# Cache options for include paths
	string(TOUPPER ${LIBRARY_TARGET} LIBRARY_TARGET_UPPER)
	string(REPLACE LIBRARY_TARGET ${LIBRARY_TARGET} DOC_INCLUDE "The include dir for LIBRARY_TARGET, empty means to use default.")
	read_cache(DEPENDENCIES_${LIBRARY_TARGET_UPPER}_INCLUDE_DIR PATH ${DEPENDENCIES_DEFAULT_INCLUDE_DIR} ${DOC_INCLUDE})
	mark_as_advanced(DEPENDENCIES_${LIBRARY_TARGET_UPPER}_INCLUDE_DIR)
	# Cache options for lib paths
	string(REPLACE LIBRARY_TARGET ${LIBRARY_TARGET} DOC_LIB "The lib dir for LIBRARY_TARGET, empty means to use default.")
	read_cache(DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIB_DIR PATH ${DEPENDENCIES_DEFAULT_LIB_DIR} ${DOC_LIB})
	mark_as_advanced(DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIB_DIR)
	
	# Add the path to lib search path of all projects
	list(APPEND CMAKE_LIBRARY_PATH ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIB_DIR})
	
	# Find the lib names
	set(DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES)
	set(DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_DEBUG)
	foreach(LIBRARY ${ARGN})
		# First try to find the release lib
		find_library(
			DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_${LIBRARY}
			NAMES ${LIBRARY}
			PATHS ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIB_DIR}
			PATH_SUFFIXES RelWithDebInfo relwithdebinfo MinSizeRel minsizerel Release release
		)
		mark_as_advanced(DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_${LIBRARY})
		list(APPEND DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_${LIBRARY}})

		# Generate debug lib names
		set(LIB_NAMES_DBG ${LIBRARY}d ${LIBRARY}D ${LIBRARY}_d ${LIBRARY}_D ${LIBRARY}_debug ${LIBRARY})

		# Find debug libraries
		find_library(
			DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_${LIBRARY}_DEBUG
			NAMES ${LIB_NAMES_DBG}
			PATHS ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIB_DIR}
			PATH_SUFFIXES Debug debug
		)
		mark_as_advanced(DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_${LIBRARY}_DEBUG)
		list(APPEND DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_DEBUG ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_${LIBRARY}_DEBUG})
	endforeach(LIBRARY)
	
	set(${LIBRARY_TARGET_UPPER}_FOUND TRUE)
	if(ARGN)
		if(DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES AND DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_DEBUG)
			# Treat them as configure-specific settings
			set(LIBRARIES)
			foreach(i ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_DEBUG})
				list(APPEND LIBRARIES debug ${i})
			endforeach(i)
			foreach(i ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES})
				list(APPEND LIBRARIES optimized ${i})
			endforeach(i)
		elseif(DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES)
			set(LIBRARIES ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES})
		elseif(DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_DEBUG)
			message(WARNING "Can't find the release version library ${LIBRARY_TARGET}.")
			set(LIBRARIES ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIBRARIES_DEBUG})
		else()
			message(WARNING "Can't find the library ${LIBRARY_TARGET}.")
			set(LIBRARIES ${ARGN})
			set(${LIBRARY_TARGET_UPPER}_FOUND FALSE)
		endif()
	endif()

	# Remember the paths
	set(${LIBRARY_TARGET}_INCLUDE_DIR ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_INCLUDE_DIR} PARENT_SCOPE)
	set(${LIBRARY_TARGET}_LIB_DIR ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIB_DIR} PARENT_SCOPE)
	set(${LIBRARY_TARGET}_LIBRARIES ${LIBRARIES} PARENT_SCOPE)

	# Output messages
	message(STATUS "Include dir: ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_INCLUDE_DIR}")
	message(STATUS "Lib dir: ${DEPENDENCIES_${LIBRARY_TARGET_UPPER}_LIB_DIR}")
	message(STATUS "Libs: ${LIBRARIES}")
	message(STATUS "")
endfunction(find_external_lib)

# Start a project source list
# Cache options: LIBRARY_TYPE_<PROJECT_NAME_UPPER>
# Global vars: CURRENT_PROJECT CURRENT_PROJECT_FULL_NAME CURRENT_PROJECT_TYPE PROJECT_FILES PROJECT_DEPENDENCIES EXTERNAL_LIBS
function(start_project PROJECT_TYPE)
	# Determine project name
	file(RELATIVE_PATH PROJECT_FULL_NAME ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
	if(ARGN)
		set(PROJECT_NAME ${ARGN})
	else()
		get_filename_component(PROJECT_NAME ${PROJECT_FULL_NAME} NAME)
	endif()
	
	# Output messages
	message(STATUS "Starting project: ${PROJECT_NAME}")

	# Check PROJECT_TYPE
	if(NOT ${PROJECT_TYPE} STREQUAL EXECUTABLE) # It's a library
		# Cache options for library type
		string(TOUPPER ${PROJECT_FULL_NAME} PROJECT_NAME_UPPER)
		string(REPLACE "/" "_" PROJECT_NAME_UPPER ${PROJECT_NAME_UPPER})
		string(REPLACE PROJECT_FULL_NAME ${PROJECT_FULL_NAME} DOC
			 "The output library type for PROJECT_FULL_NAME, options are STATIC, SHARED and MODULE, or empty which means to use default."
		)
		if(${PROJECT_TYPE} STREQUAL "LIBRARY")
			set(LIBRARY_TYPE "")
		else()
			set(LIBRARY_TYPE ${PROJECT_TYPE})
		endif()
		set(LIBRARY_TYPE_${PROJECT_NAME_UPPER} ${LIBRARY_TYPE} CACHE STRING ${DOC})
		mark_as_advanced(LIBRARY_TYPE_${PROJECT_NAME_UPPER})
		
		# If empty, use default setting
		if(NOT LIBRARY_TYPE_${PROJECT_NAME_UPPER})
			set(LIBRARY_TYPE_${PROJECT_NAME_UPPER} ${DEFAULT_LIBRARY_TYPE})
		endif()
		set(PROJECT_TYPE ${LIBRARY_TYPE_${PROJECT_NAME_UPPER}})
	endif()
	string(REPLACE "/" "_" PROJECT_FULL_NAME ${PROJECT_FULL_NAME})
	string(REPLACE "\\" "_" PROJECT_FULL_NAME ${PROJECT_FULL_NAME})

	message(STATUS "Project FullName: ${PROJECT_FULL_NAME}")

	# Start a project
	project(${PROJECT_NAME})
	
	# Remember the vars
	set(CURRENT_PROJECT ${PROJECT_NAME} PARENT_SCOPE)
	set(CURRENT_PROJECT_FULL_NAME ${PROJECT_FULL_NAME} PARENT_SCOPE)
	set(CURRENT_PROJECT_TYPE ${PROJECT_TYPE} PARENT_SCOPE)
	set(PROJECT_FILES PARENT_SCOPE)
	set(PROJECT_DEPENDENCIES PARENT_SCOPE)
	set(EXTERNAL_LIBS PARENT_SCOPE)
	
	# Output messages
	message(STATUS "Short name: ${PROJECT_NAME_SHORT}")
	message(STATUS "Project type: ${PROJECT_TYPE}")
endfunction(start_project)

# Add an option
function(add_option OPTION_NAME DOCUMENT DEFAULT_VALUE)
	option (${OPTION_NAME} ${DOCUMENT} ${DEFAULT_VALUE}) 
	if (${OPTION_NAME})
		add_definitions(-D${OPTION_NAME})
	endif (${OPTION_NAME})
endfunction(add_option)

# Glob all the sources to the source list
# Global vars: PROJECT_FILES
function(glob_source SUB_DIRECTORY)
	# Determine sub directory
	if(SUB_DIRECTORY)
		set(PREFIX ${SUB_DIRECTORY}/)
	else()
		set(PREFIX)
	endif()
	
	# Glob the source files
	file(GLOB FILES_GLOB RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
		${PREFIX}*.hpp ${PREFIX}*.h ${PREFIX}*.hxx ${PREFIX}*.hh ${PREFIX}*.h++
		${PREFIX}*.cpp ${PREFIX}*.c ${PREFIX}*.cc ${PREFIX}*.C ${PREFIX}*.c++ ${PREFIX}*.cxx
	)
	
	# Add the sources
	if(SUB_DIRECTORY)
		add_source(GROUP ${SUB_DIRECTORY} ${FILES_GLOB})
	else()
		add_source(${FILES_GLOB})
	endif()
	
	# Remember all sources
	set(PROJECT_FILES ${PROJECT_FILES} PARENT_SCOPE)
endfunction(glob_source)

# Add a source file to the source list
# Global vars: PROJECT_FILES
function(add_source)
	# If the param is beginning with "GROUP", substract the group option
	if((${ARGC} GREATER 1) AND (ARGV0 STREQUAL GROUP))
		set(GROUP ${ARGV1})
		list(REMOVE_AT ARGV 0)
		list(REMOVE_AT ARGV 0)
	else()
		set(GROUP)
	endif()
	
	# Add all sources
	set(NEW_PROJECT_FILES ${ARGV})
	
	# Comment out, for we can use GBK encoding for both Windows and Linux
	## Generate NoBOM files
	#if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	#	set(NOBOM_PROJECT_FILES)
	#	
	#	foreach(SOURCE_NAME ${NEW_PROJECT_FILES})
	#		get_filename_component(FILEPATH ${SOURCE_NAME} PATH)
	#		set(NOBOM_PATH ${NO_BOM_PATH_SUFFIX}/${FILEPATH})
	#		set(NOBOM_SOURCE_NAME ${NO_BOM_PATH_SUFFIX}/${SOURCE_NAME})
	#		add_custom_command(
	#			OUTPUT ${NOBOM_SOURCE_NAME}
	#			COMMAND mkdir -p ${NOBOM_PATH}
	#			COMMAND awk '{if(NR==1)sub(/^\\xef\\xbb\\xbf/, \"\")\;print}' ${SOURCE_NAME} > ${NOBOM_SOURCE_NAME}
	#			MAIN_DEPENDENCY ${SOURCE_NAME}
	#		)
	#		list(APPEND NOBOM_PROJECT_FILES ${NOBOM_SOURCE_NAME})
	#	endforeach(SOURCE_NAME)
	#	
	#	set(NEW_PROJECT_FILES ${NOBOM_PROJECT_FILES})
	#endif()
	
	# Add build rule for .idl files
	#foreach(SOURCE_NAME ${NEW_PROJECT_FILES})
	#	get_filename_component(FILEEXT ${SOURCE_NAME} EXT)
	#	if(FILEEXT STREQUAL .idl)
	#		string(REPLACE .idl .h IDL_FILE_TARGET ${SOURCE_NAME})
	#		add_custom_command(
	#			OUTPUT ${IDL_FILE_TARGET}
	#			COMMAND ./Serialization ${SOURCE_NAME}
	#			MAIN_DEPENDENCY ${SOURCE_NAME}
	#		)
	#		list(APPEND NEW_PROJECT_FILES ${IDL_FILE_TARGET})
	#	endif()
	#endforeach(SOURCE_NAME)
	
	# Add the sources to source_group, which is used mainly by msvc
	if(GROUP AND NEW_PROJECT_FILES)
		string(REPLACE "/" "\\" GROUP ${GROUP})
		source_group(${GROUP} FILES ${NEW_PROJECT_FILES})
	endif()
	
	# Remember all sources
	set(PROJECT_FILES ${PROJECT_FILES} ${NEW_PROJECT_FILES} PARENT_SCOPE)
endfunction(add_source)

# Remove a source file from the source list
# Global vars: PROJECT_FILES
function(remove_source SOURCE_NAME)
	list(REMOVE_ITEM PROJECT_FILES ${SOURCE_NAME})
	set(PROJECT_FILES ${PROJECT_FILES} PARENT_SCOPE)
endfunction(remove_source)

# Add dependencies of projects
# Global vars: PROJECT_DEPENDENCIES
function(depend_on_project)
	foreach(TARGETNAME ${ARGN})
		if(NOT ${TARGETNAME}_SOURCE_DIR)
			message(WARNING "Can't find the library ${TARGETNAME}.")
		endif()
		list(APPEND PROJECT_DEPENDENCIES ${TARGETNAME})
	endforeach()
	set(PROJECT_DEPENDENCIES ${PROJECT_DEPENDENCIES} PARENT_SCOPE)
endfunction(depend_on_project)

# Link to a external library
# Global vars: EXTERNAL_LIBS
function(include_external_lib LIBRARY_TARGET)
	set(EXTERNAL_LIBS ${EXTERNAL_LIBS} ${LIBRARY_TARGET} PARENT_SCOPE)
endfunction(include_external_lib)

# Finish the description of a project
function(end_project)
	#if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	#	set(PROJECT_INCLUDE_SUFFIX /${NO_BOM_PATH_SUFFIX})
	#else()
	#	set(PROJECT_INCLUDE_SUFFIX)
	#endif()
	
	# Add the current src dir as include dir
	include_directories(${CMAKE_CURRENT_SOURCE_DIR})

	# Add include dir for dependencies
	foreach(PROJECT_DEPENDENCY ${PROJECT_DEPENDENCIES})
		if(EXISTS ${${PROJECT_DEPENDENCY}_SOURCE_DIR}/include)
			include_directories(${${PROJECT_DEPENDENCY}_SOURCE_DIR}/include)
		else()
			include_directories(${${PROJECT_DEPENDENCY}_SOURCE_DIR})
		endif()
	endforeach(PROJECT_DEPENDENCY)
	
	# Add include dir for external libs
	foreach(EXTERNAL_LIB ${EXTERNAL_LIBS})
		include_directories(${${EXTERNAL_LIB}_INCLUDE_DIR})
	endforeach(EXTERNAL_LIB)
	
	# Add link path for external libs
	if(CMAKE_LIBRARY_PATH)
		link_directories(${CMAKE_LIBRARY_PATH})
	endif()

	# Add sources
	list(REMOVE_DUPLICATES PROJECT_FILES)
	if(${CURRENT_PROJECT_TYPE} STREQUAL EXECUTABLE)
		add_executable(${CURRENT_PROJECT} ${PROJECT_FILES})
	else()
		add_library(${CURRENT_PROJECT} ${CURRENT_PROJECT_TYPE} ${PROJECT_FILES})
	endif()

	# Set the IDE project name to full name
	set_target_properties(${CURRENT_PROJECT} PROPERTIES PROJECT_LABEL ${CURRENT_PROJECT_FULL_NAME})
	
	# Add link for dependencies
	foreach(PROJECT_DEPENDENCY ${PROJECT_DEPENDENCIES})
		target_link_libraries(${CURRENT_PROJECT} ${PROJECT_DEPENDENCY})
		#add_dependencies(${CURRENT_PROJECT} ${PROJECT_DEPENDENCY})
	endforeach(PROJECT_DEPENDENCY)

	# Add link for external libs
	foreach(EXTERNAL_LIB ${EXTERNAL_LIBS})
		target_link_libraries(${CURRENT_PROJECT} ${${EXTERNAL_LIB}_LIBRARIES})
	endforeach(EXTERNAL_LIB)
	
	# Output messages
	message(STATUS "Project dependencies: ${PROJECT_DEPENDENCIES}")
	message(STATUS "External libs: ${EXTERNAL_LIBS}")
	message(STATUS "")
endfunction(end_project)




