cmake_minimum_required(VERSION 3.25.2)

project(regsys)

add_executable(reg 
    src/core.cpp
    src/main.cpp
    src/object.cpp
    src/primitive.cpp
    src/win.cpp)

target_include_directories(reg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
