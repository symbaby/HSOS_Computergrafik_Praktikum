cmake_minimum_required(VERSION 3.19.2)
project(CGPrakt1)

set(CMAKE_CXX_STANDARD 14)

add_executable(CGPrakt2 main.cpp
        include/color.h include/rgbimage.h include/vector.h
        lib/color.cpp lib/rgbimage.cpp lib/vector.cpp
        test/test1.h test/test2.h test/test3.h test/test1.cpp test/test2.cpp test/test3.cpp lib/CGUtilities.cpp include/CGUtilities.h lib/SimpleRayTracer.cpp include/SimpleRayTracer.h)
