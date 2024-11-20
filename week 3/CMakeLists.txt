cmake_minimum_required(VERSION 3.26)
project(week3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(data)
include_directories(/usr/local/include/nifti)
include_directories(/opt/X11/include)

add_executable(week3
        data/football.nii.gz
        data/brainT1.nii.gz
        data/xslice.bmp
        data/yslice.bmp
        data/zslice.bmp
        image.hpp
        niftiio.hpp
        week3.cpp
        bmpmini.hpp
)

target_link_libraries(week3
        -L/usr/local/lib -lniftiio -lznz -lz
        -L/opt/X11/lib -lX11
)