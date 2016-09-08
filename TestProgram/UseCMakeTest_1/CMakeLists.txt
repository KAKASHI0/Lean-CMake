cmake_minimum_required (VERSION 2.6)

PROJECT (HELLO)

set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

configure_file ( "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in" 
		"${PROJECT_BINARY_DIR}/TutorialConfig.h" 
		)
		
SET (SRC_LIST UseCMakeTest_1.cpp)
include_directories("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")

option (USE_MYMATH "Use tutorial provided math implementation" ON)
if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
  add_subdirectory (MathFunctions)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# add the executable
add_executable (hello ${SRC_LIST})
target_link_libraries (hello  ${EXTRA_LIBS})

# add the install targets
install (TARGETS hello DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)

# enable_testing 和 include(CTest) 论区别 不明朗		 
enable_testing()		 
#include(CTest)

# does the application run
add_test (TutorialRuns hello 25)

# does it sqrt of 25
add_test (TutorialComp25 hello 25)

set_tests_properties (TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 1")

# does it handle negative numbers
add_test (TutorialNegative hello -25)
set_tests_properties (TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is 0")

# does it handle small numbers
add_test (TutorialSmall hello 0.0001)
set_tests_properties (TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")

# does the usage message work?
add_test (TutorialUsage hello)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")
