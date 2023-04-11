# Set minimum allowed CMAKE to build with
cmake_minimum_required(VERSION 3.10)
add_library(Glad glad.c)

target_include_directories(
    Glad
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
