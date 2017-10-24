cmake_minimum_required(VERSION 3.8)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

aux_source_directory(. SOURCE_FILES)

# install(DIRECTORY . DESTINATION ${PROJECT_SOURCE_DIR}/include FILES_MATCHING PATTERN "*.h")
