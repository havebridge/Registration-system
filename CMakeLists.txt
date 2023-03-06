cmake_minimum_required(VERSION 3.25.2)

project(regsys)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

#add_subdirectory(external/hserialize)


target_include_directories(${PROJECT_NAME}  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
