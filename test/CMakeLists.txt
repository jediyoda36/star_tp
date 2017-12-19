cmake_minimum_required(VERSION 3.8)

include_directories(${PROJECT_SOURCE_DIR}/src)

aux_source_directory(../src SRC_FILES)

add_executable(testFuturePromiseAsync TestFuturePromiseAsync.cpp)
if (UNIX AND NOT APPLE)
    target_link_libraries(testFuturePromiseAsync pthread)
endif()

add_executable(testPackagedTask TestPackagedTask.cpp)
if (UNIX AND NOT APPLE)
    target_link_libraries(testPackagedTask pthread)
endif()

add_executable(testFunctionAndBind TestFunctionAndBind.cpp)

add_executable(testMove TestMove.cpp)

add_executable(testCTask TestCTask.cpp ${SRC_FILES})
if (APPLE)
    target_link_libraries(testCTask boost_system-mt)
    target_link_libraries(testCTask boost_thread-mt)
elseif (UNIX)
    target_link_libraries(testCTask pthread)
    target_link_libraries(testCTask boost_system)
    target_link_libraries(testCTask boost_thread)
endif()

add_executable(testCThreadPool TestCThreadPool.cpp ${SRC_FILES})
if (APPLE)
    target_link_libraries(testCThreadPool boost_system-mt)
    target_link_libraries(testCThreadPool boost_thread-mt)
elseif (UNIX AND NOT APPLE)
    target_link_libraries(testCThreadPool pthread)
    target_link_libraries(testCThreadPool boost_system)
    target_link_libraries(testCThreadPool boost_thread)
endif()

