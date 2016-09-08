add_library(MathFunctions mysqrt.cpp)
install (TARGETS MathFunctions DESTINATION bin)
install (FILES mysqrt.h DESTINATION include)