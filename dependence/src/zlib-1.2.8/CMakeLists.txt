############################################################
# zlib library
############################################################

start_project(LIBRARY zlib)

add_source(src/adler32.c)
add_source(src/compress.c)
add_source(src/crc32.c)
add_source(src/deflate.c)
add_source(src/gzclose.c)
add_source(src/gzlib.c)
add_source(src/gzread.c)
add_source(src/gzwrite.c)
add_source(src/inflate.c)
add_source(src/infback.c)
add_source(src/inftrees.c)
add_source(src/inffast.c)
add_source(src/trees.c)
add_source(src/uncompr.c)
add_source(src/zutil.c)
	
include_directories(include)

end_project()