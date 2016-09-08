############################################################
# luabind library
############################################################

start_project(LIBRARY luabind)

glob_source(src)
depend_on_project(lua)
include_external_lib(Boost)

install(DIRECTORY luabind DESTINATION include FILES_MATCHING PATTERN *.hpp PATTERN *.h PATTERN *.hxx)

end_project()

