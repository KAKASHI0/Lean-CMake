# Use relative paths
# This is mostly to reduce path size for command-line limits on windows
if(WIN32)
	set(CMAKE_USE_RELATIVE_PATHS true)
	set(CMAKE_SUPPRESS_REGENERATION true)
endif()

# Default build type is ReleaseWithDebugInfo
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR} CACHE STRING "Install path prefix, prepended onto install directories." FORCE)
set(DEFAULT_LIBRARY_TYPE "STATIC" CACHE STRING "The default output library type, options are STATIC, SHARED and MODULE.")

# Default link path
set(CMAKE_LIBRARY_PATH ${DEPENDENCIES_DEFAULT_LIB_DIR})

# Specify build paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# For linux, use _d postfix for Debug
if(UNIX)
	set(CMAKE_DEBUG_POSTFIX _d)
	set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -pg -static")
	set(LINK_FLAGS "-pg")
	set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -g -ggdb -pg -static")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "$ENV{CXXFLAGS} -O4 -Wall -g -ggdb -pg -static")
	add_definitions(-march=x86-64)
#	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")	
endif()

# For msvc, use static runtime. Will ignore /MDd /MD options in the cache.
if(MSVC_USE_STATIC_RUNTIME)
	if(MSVC)
		set(CXX_FLAGS_VARS CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
		set(C_FLAGS_VARS CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
		set(FLAGS_VARS ${CXX_FLAGS_VARS} ${C_FLAGS_VARS})
		foreach(flag_var ${FLAGS_VARS})
			if(${flag_var} MATCHES "/MD")
				# Replace /MD with /MT
				string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
			endif(${flag_var} MATCHES "/MD")
		endforeach(flag_var)
	endif()
endif()

