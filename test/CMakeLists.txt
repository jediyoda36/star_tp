cmake_minimum_required(VERSION 3.8)

include_directories(${PROJECT_SOURCE_DIR}/src)

aux_source_directory(../src SRC_FILES)

add_executable(testFuturePromiseAsync TestFuturePromiseAsync.cpp)
target_link_libraries(testFuturePromiseAsync pthread)

add_executable(testPackagedTask TestPackagedTask.cpp)
target_link_libraries(testPackagedTask pthread)

add_executable(testFunctionAndBind TestFunctionAndBind.cpp)

add_executable(testMove TestMove.cpp)

#add_executable(testStartp TestStartp.cpp)
#target_link_libraries(testPackagedTask pthread)

add_executable(testCTask TestCTask.cpp ${SRC_FILES})
target_link_libraries(testCTask pthread)
target_link_libraries(testCTask boost_system)
target_link_libraries(testCTask boost_thread)

add_executable(testCThreadPool TestCThreadPool.cpp ${SRC_FILES})
target_link_libraries(testCThreadPool pthread)
target_link_libraries(testCThreadPool boost_system)
target_link_libraries(testCThreadPool boost_thread)

