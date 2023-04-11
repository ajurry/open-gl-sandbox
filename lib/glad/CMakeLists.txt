# Set minimum allowed CMAKE to build with
cmake_minimum_required(VERSION 3.10)
add_library(Glad glad.c)

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/include/glad")

target_include_directories(
    Glad 
    INTERFACE 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/include/glad"
)
