cmake_minimum_required(VERSION 3.26)
project(Week1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(CImg)
include_directories(data)
include_directories(week1)
include_directories(/usr/local/include/nifti)
include_directories(/opt/X11/include)

add_executable(Week1
        CImg/CImg.h
        data/brainT1.nii.gz
        data/brainT1_week1.bmp
        week1/image.hpp
        week1/niftiio.hpp
        week1/week1.cpp
        week1/week1.project)

target_link_libraries(Week1
        -L/usr/local/lib -lniftiio -lznz -lz
        -L/opt/X11/lib -lX11
)