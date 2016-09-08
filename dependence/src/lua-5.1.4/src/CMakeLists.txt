############################################################
# lua library
############################################################

start_project(LIBRARY lua)

glob_source("")
remove_source(print.c)
remove_source(lua.c)
remove_source(luac.c)

install(FILES lauxlib.h lua.h luaconf.h lualib.h ../etc/lua.hpp DESTINATION include/lua)

end_project()

