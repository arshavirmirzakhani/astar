cmake_minimum_required(VERSION 3.10)

project(astar)

add_subdirectory(vendor/SDL/)

set(SOURCE_FILES main.cpp)

add_executable(astar ${SOURCE_FILES})

target_link_libraries(astar PRIVATE SDL3-static)
target_link_directories(astar PRIVATE ${CMAKE_BINARY_DIR}/vendor/SDL/Debug)

target_include_directories(astar PRIVATE ${PROJECT_SOURCE_DIR}/vendor/SDL/include)