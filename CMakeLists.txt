cmake_minimum_required(VERSION 3.10)

project(astar)

add_subdirectory(vendor/SDL/)

file(GLOB_RECURSE SOURCES_BIN "${CMAKE_CURRENT_SOURCE_DIR}/engine/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
add_executable(astar ${SOURCES_BIN})

target_link_libraries(astar PRIVATE SDL3-static)
target_link_directories(astar PRIVATE ${CMAKE_BINARY_DIR}/vendor/SDL/Debug)

target_include_directories(astar PRIVATE ${PROJECT_SOURCE_DIR}/vendor/SDL/include ${PROJECT_SOURCE_DIR}/vendor/gzip)