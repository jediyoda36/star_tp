cmake_minimum_required(VERSION 3.8)

project(chapter09)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-lpthread")

set(SOURCE_FILES
    main.cpp
    JoinThreads.h
    ThreadSafeQueue.h
    SimpleThreadPool.h
    )

add_executable(chapter09 ${SOURCE_FILES})
target_link_libraries(chapter09 -lpthread)

