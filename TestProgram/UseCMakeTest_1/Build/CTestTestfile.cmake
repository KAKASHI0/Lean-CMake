# CMake generated Testfile for 
# Source directory: G:/TestProgram/UseCMakeTest_1
# Build directory: G:/TestProgram/UseCMakeTest_1/Build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(TutorialRuns "hello" "25")
add_test(TutorialComp25 "hello" "25")
set_tests_properties(TutorialComp25 PROPERTIES  PASS_REGULAR_EXPRESSION "25 is 1")
add_test(TutorialNegative "hello" "-25")
set_tests_properties(TutorialNegative PROPERTIES  PASS_REGULAR_EXPRESSION "-25 is 0")
add_test(TutorialSmall "hello" "0.0001")
set_tests_properties(TutorialSmall PROPERTIES  PASS_REGULAR_EXPRESSION "0.0001 is 0.01")
add_test(TutorialUsage "hello")
set_tests_properties(TutorialUsage PROPERTIES  PASS_REGULAR_EXPRESSION "Usage:.*number")
subdirs(MathFunctions)
