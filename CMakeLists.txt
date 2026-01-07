cmake_minimum_required(VERSION 3.23)

project(ds_tetris LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE DS_TETRIS_SOURCES
     CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/ds_tetris/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/ds_tetris/*.hpp
)

add_executable(main ${DS_TETRIS_SOURCES})

target_include_directories(main
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ds_tetris
)

target_compile_options(main PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
    -Wshadow
    -Wold-style-cast
    -Woverloaded-virtual
    -Wnon-virtual-dtor
    -Wnull-dereference
    -Wdouble-promotion
    -Wformat=2
    -Wimplicit-fallthrough
    -Werror
)

target_compile_definitions(main PRIVATE
    $<$<CONFIG:Debug>:_GLIBCXX_ASSERTIONS>
)