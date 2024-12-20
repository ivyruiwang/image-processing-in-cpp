cmake_minimum_required(VERSION 3.26)
project(final_assignment)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(amipractical_data)
include_directories(/usr/local/include/nifti)
include_directories(/opt/X11/include)

add_executable(final_assignment
#        GPT.cpp
        image.hpp
        main.cpp
        niftiio.hpp
        bmpmini.hpp
        main.cpp)

target_link_libraries(final_assignment
        -L/usr/local/lib -lniftiio -lznz -lz
        -L/opt/X11/lib -lX11
)