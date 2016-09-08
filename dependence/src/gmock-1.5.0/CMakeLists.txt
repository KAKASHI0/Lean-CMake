############################################################
# gmock library
############################################################

start_project(LIBRARY gmock)

add_source(src/gmock-all.cc)
include_directories(gtest/include)
include_directories(include)

#install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN *.hpp PATTERN *.h PATTERN *.hxx)

end_project()

