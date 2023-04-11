# Set minimum allowed CMAKE to build with
cmake_minimum_required(VERSION 3.10)

# Set the project name and the current version of it
project(OpenGL VERSION 1.0)

# Specify the C++ standard and that the standard library should be used
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# To generate the configuration file containing build parameters
configure_file(OpenGLConfig.h.in OpenGLConfig.h)

# Added GLFW directory and append the library to build
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add required sub-directories for current libraries
# TODO: This is messy, should have it iterate over all the folders in lib
add_subdirectory(lib/glfw-3.3.8)
add_subdirectory(lib/glad)

# Added all library dependencies
list(
    APPEND __LIBS 
    lib/glfw-3.3.8/src/debug/glfw3 
    lib/glad/debug/glad
)

# Executable used for running
add_executable(
    main main.cpp
)

# Linking against external libraries such as OpenGL
target_link_libraries(
    main PUBLIC ${__LIBS}
)

# Add the required target include directories
# This is a bit messy, as I should be able to remove the soure_dir include reference
# TODO: Remove the source dir reference
target_include_directories(
    main PUBLIC 
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"    
    "${PROJECT_SOURCE_DIR}/include/glad"
)
