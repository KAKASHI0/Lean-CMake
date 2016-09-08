############################################################
# gtest library
############################################################

start_project(LIBRARY gtest)

add_source(src/gtest-all.cc)
include_directories(.)
include_directories(include)

install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN *.hpp PATTERN *.h PATTERN *.hxx)

end_project()

