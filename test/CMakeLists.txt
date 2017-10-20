cmake_minimum_required(VERSION 3.8)

include_directories(${PROJECT_SOURCE_DIR}/include)

# set(SOURCE_FILES
    # main.cpp
    # JoinThreads.h
    # ThreadSafeQueue.h
    # SimpleThreadPool.h
    # )

# aux_source_directory(. TEST_SRC_FILES)

add_executable(testFuturePromiseAsync TestFuturePromiseAsync.cpp)
target_link_libraries(testFuturePromiseAsync pthread)

add_executable(testPackagedTask TestPackagedTask.cpp)
target_link_libraries(testPackagedTask pthread)

add_executable(testSimpleThreadPool TestSimpleThreadPool.cpp)
target_link_libraries(testSimpleThreadPool pthread)
