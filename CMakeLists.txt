cmake_minimum_required(VERSION 3.26.0)
project(arcadia VERSION 1.0.0)
cmake_policy( SET CMP0072 NEW )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# ImGui paths
set(IMGUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/include/imgui)
set(IMGUI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/lib/imgui)

# ImGui sources
set(IMGUI_SOURCES
    ${IMGUI_SOURCE_DIR}/imgui.cpp
    ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
    ${IMGUI_SOURCE_DIR}/imgui_tables.cpp
    ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
    ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# ImGui static library
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
    external/include
    ${IMGUI_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}/backends
)

target_link_libraries( imgui 
    ${GLFW3_LIBRARY}
)

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

target_include_directories(arcadia PRIVATE external/include ${CMAKE_SOURCE_DIR}/source)

target_link_libraries(arcadia
    ${GLFW3_LIBRARY}
    OpenGL::GL
    imgui
)