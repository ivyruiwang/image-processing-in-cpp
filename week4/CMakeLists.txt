cmake_minimum_required(VERSION 3.26)
project(week4)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++11-narrowing")

include_directories(.)
include_directories(amipractical_data)
include_directories(/usr/local/include/nifti)
include_directories(/opt/X11/include)

add_executable(week4
        amipractical_data/brainT1.nii.gz
        image.hpp
        niftiio.hpp
        week_mt.cpp
        bmpmini.hpp)

target_link_libraries(week4
        -L/usr/local/lib -lniftiio -lznz -lz
        -L/opt/X11/lib -lX11
)