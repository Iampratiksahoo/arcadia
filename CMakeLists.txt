cmake_minimum_required(VERSION 3.26.0)
project(arcadia VERSION 1.0.0)
cmake_policy( SET CMP0072 NEW )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Recursively add all source files in the source directory
file(
    GLOB_RECURSE 
    SOURCE_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/source/*.c
)

add_executable(arcadia 
    ${SOURCE_FILES}
)

target_include_directories(arcadia PRIVATE external/include)
include_directories(PRIVATE ${CMAKE_SOURCE_DIR}/source)

target_link_libraries(arcadia
    ${GLFW3_LIBRARY}
    OpenGL::GL
)