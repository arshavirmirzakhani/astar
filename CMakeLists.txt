cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(astar)
project(astar_editor)

add_subdirectory(vendor/SDL3/)

file(GLOB_RECURSE SOURCES_ENGINE "${CMAKE_CURRENT_SOURCE_DIR}/engine_bin/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp")
add_executable(astar ${SOURCES_ENGINE})

target_link_libraries(astar PRIVATE SDL3-static)
target_link_directories(astar PRIVATE ${CMAKE_BINARY_DIR}/vendor/SDL/Debug)

target_include_directories(astar PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/vendor/SDL3/ ${PROJECT_SOURCE_DIR}/vendor/gzip ${PROJECT_SOURCE_DIR}/vendor/)


file(GLOB_RECURSE SOURCES_EDITOR "${CMAKE_CURRENT_SOURCE_DIR}/editor/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp")
add_executable(astar_editor ${SOURCES_EDITOR})

target_link_libraries(astar_editor PRIVATE SDL3-static)
target_link_directories(astar_editor PRIVATE ${CMAKE_BINARY_DIR}/vendor/SDL/Debug)

target_include_directories(astar_editor PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/vendor/SDL3/ ${PROJECT_SOURCE_DIR}/vendor/gzip ${PROJECT_SOURCE_DIR}/vendor/ ${PROJECT_SOURCE_DIR}/editor/src ${PROJECT_SOURCE_DIR}/editor/src/imgui)