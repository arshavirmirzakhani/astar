cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} /DEF:my_defs.def /NODEFAULTLIB")
endif()

project(astar)

# Source groups
file(GLOB_RECURSE SOURCES_ENGINE "${CMAKE_CURRENT_SOURCE_DIR}/engine_bin/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp")
file(GLOB_RECURSE SOURCES_EDITOR "${CMAKE_CURRENT_SOURCE_DIR}/editor/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp")

# Common include paths
set(COMMON_INCLUDES
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/vendor/SDL2/include/
    ${PROJECT_SOURCE_DIR}/vendor/SDL2/
    ${PROJECT_SOURCE_DIR}/vendor/lua/lua-5.4.7/include
    ${PROJECT_SOURCE_DIR}/vendor/
)

add_executable(astar ${SOURCES_ENGINE})
target_include_directories(astar PRIVATE ${COMMON_INCLUDES})

add_executable(astar_editor ${SOURCES_EDITOR})
target_include_directories(astar_editor PRIVATE ${COMMON_INCLUDES}
    ${PROJECT_SOURCE_DIR}/editor/src
    ${PROJECT_SOURCE_DIR}/editor/src/imgui
)

# SDL and Lua
if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    add_subdirectory(vendor/SDL2)
    add_subdirectory(vendor/lua)
    
    target_link_options(astar PRIVATE -sUSE_SDL=2 -sALLOW_MEMORY_GROWTH=1 -sEXPORTED_RUNTIME_METHODS=['FS','callMain'] --preload-file ${CMAKE_SOURCE_DIR}/assets@assets)
    target_link_options(astar_editor PRIVATE -sUSE_SDL=2 -sALLOW_MEMORY_GROWTH=1 -sEXPORTED_RUNTIME_METHODS=['FS','callMain'] --preload-file ${CMAKE_SOURCE_DIR}/assets@assets)

    target_link_libraries(astar PRIVATE lua_static)
    target_link_libraries(astar_editor PRIVATE lua_static)

else()
    add_subdirectory(vendor/SDL2)
    add_subdirectory(vendor/lua)

    target_link_libraries(astar PRIVATE SDL2maind SDL2-static lua_static)
    target_link_libraries(astar_editor PRIVATE SDL2maind SDL2-static lua_static)


    target_link_directories(astar PRIVATE ${CMAKE_BINARY_DIR}/vendor/SDL2/Debug)
    target_link_directories(astar_editor PRIVATE ${CMAKE_BINARY_DIR}/vendor/SDL2/Debug)
endif()
