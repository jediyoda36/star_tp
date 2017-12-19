cmake_minimum_required(VERSION 3.8)

project(star_tp)

set(CMAKE_CXX_STANDARD 11)
if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-lpthread")
endif()

add_subdirectory(src)
add_subdirectory(test)
