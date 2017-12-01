cmake_minimum_required(VERSION 3.8)

aux_source_directory(. SOURCE_FILES)

add_library(star ${SOURCE_FILES})

install(DIRECTORY . DESTINATION ${PROJECT_SOURCE_DIR}/include FILES_MATCHING PATTERN "*.h")
install(DIRECTORY . DESTINATION ${PROJECT_SOURCE_DIR}/lib FILES_MATCHING PATTERN "*.a")
