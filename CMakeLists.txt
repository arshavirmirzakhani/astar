cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

# Detect Emscripten build
if (EMSCRIPTEN)
    message(STATUS "Emscripten build detected")
endif()

project(astar)

# Source groups
file(GLOB_RECURSE SOURCES_ENGINE "${CMAKE_CURRENT_SOURCE_DIR}/engine_bin/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp")
file(GLOB_RECURSE SOURCES_EDITOR "${CMAKE_CURRENT_SOURCE_DIR}/editor/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp")

# Common include paths
set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/vendor/SDL3/include/SDL3
    ${PROJECT_SOURCE_DIR}/vendor/SDL3/include/
    ${PROJECT_SOURCE_DIR}/vendor/SDL3/
    ${PROJECT_SOURCE_DIR}/vendor/lua/lua-5.4.7/include
    ${PROJECT_SOURCE_DIR}/vendor/
)

# Astar Engine Target
add_executable(astar ${SOURCES_ENGINE})
target_include_directories(astar PRIVATE ${COMMON_INCLUDES})

# Editor Target
add_executable(astar_editor ${SOURCES_EDITOR})
target_include_directories(astar_editor PRIVATE ${COMMON_INCLUDES}
    ${PROJECT_SOURCE_DIR}/editor/src
    ${PROJECT_SOURCE_DIR}/editor/src/imgui
)

# Link SDL and Lua differently for Emscripten
if(EMSCRIPTEN)
    # Use Emscripten's built-in SDL support
    set(CMAKE_EXECUTABLE_SUFFIX ".html")  # Generates .html/.wasm/.js

    add_subdirectory(vendor/SDL3)
    add_subdirectory(vendor/lua)

    target_link_options(astar PRIVATE -sUSE_SDL=0 -sALLOW_MEMORY_GROWTH=1 -sEXPORTED_RUNTIME_METHODS=['FS','callMain'] --preload-file assets)
    target_link_options(astar_editor PRIVATE -sUSE_SDL=0 -sALLOW_MEMORY_GROWTH=1 -sEXPORTED_RUNTIME_METHODS=['FS','callMain'] --preload-file assets)

    target_link_libraries(astar PRIVATE lua_static)
    target_link_libraries(astar_editor PRIVATE lua_static)

else()
    # Native build
    add_subdirectory(vendor/SDL3/)
    add_subdirectory(vendor/lua)

    target_link_libraries(astar PRIVATE SDL3-static lua_static)
    target_link_directories(astar PRIVATE ${CMAKE_BINARY_DIR}/vendor/SDL/Debug ${CMAKE_BINARY_DIR}/vendor/lua/lua-5.4.7/Debug)

    target_link_libraries(astar_editor PRIVATE SDL3-static lua_static)
    target_link_directories(astar_editor PRIVATE ${CMAKE_BINARY_DIR}/vendor/SDL/Debug ${CMAKE_BINARY_DIR}/vendor/lua/lua-5.4.7/Debug)
endif()
