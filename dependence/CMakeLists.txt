cmake_minimum_required(VERSION 2.6)

#####################################################################
# Options
#####################################################################
option(MSVC_USE_STATIC_RUNTIME "For MSVC, use static runtime libraries instead of the default dll runtime libraries." ON)
set(DEPENDENCIES_DEFAULT_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include CACHE PATH "The default include dir for 3rd-party dependencies")
set(DEPENDENCIES_DEFAULT_LIB_DIR ${CMAKE_SOURCE_DIR}/lib CACHE PATH "The default lib dir for 3rd-party dependencies")

#####################################################################
# Project start
#####################################################################
project(Dependencies)

# Include necessary submodules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(BuildConfigs)
include(SimpleProject)

find_external_lib(Boost)

add_subdirectory(src/gmock-1.5.0/gtest)
add_subdirectory(src/gmock-1.5.0)
add_subdirectory(src/lua-5.1.4/src)
add_subdirectory(src/luabind-0.9.1)
add_subdirectory(src/zlib-1.2.8)

