cmake_minimum_required(VERSION 3.10)

project(astar)
project(astar_editor)

add_subdirectory(vendor/SDL/)

file(GLOB_RECURSE SOURCES_ENGINE "${CMAKE_CURRENT_SOURCE_DIR}/engine/src/*.cpp")
add_executable(astar ${SOURCES_ENGINE})

file(GLOB_RECURSE SOURCES_EDITOR "${CMAKE_CURRENT_SOURCE_DIR}/editor/src/*.cpp")
add_executable(astar_editor ${SOURCES_EDITOR})

target_link_libraries(astar PRIVATE SDL3-static)
target_link_directories(astar PRIVATE ${CMAKE_BINARY_DIR}/vendor/SDL/Debug)

target_include_directories(astar PRIVATE ${PROJECT_SOURCE_DIR}/vendor/SDL/include ${PROJECT_SOURCE_DIR}/vendor/gzip ${PROJECT_SOURCE_DIR}/vendor/imgui)