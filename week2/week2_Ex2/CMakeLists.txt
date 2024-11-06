cmake_minimum_required(VERSION 3.26)
project(week2_Ex2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(data)

add_executable(week2_Ex2
        data/brainT1.img
        data/brainT1.hdr
        data/brainT1_week2.bmp
        bmpmini.hpp
        image.hpp
        main.cpp
        Tools.cpp
        Tools.hpp)

target_link_libraries(week2_Ex2
        -L/opt/X11/lib -lX11
)