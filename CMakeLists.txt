cmake_minimum_required(VERSION 3.8)

project(star_tp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-lpthread")

add_subdirectory(src)
add_subdirectory(test)
