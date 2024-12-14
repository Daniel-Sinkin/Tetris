cmake_minimum_required(VERSION 3.16)

project(tetris VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(tetris.o src/main.c)

target_include_directories(tetris.o PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(tetris.o PRIVATE ${SDL2_LIBRARIES})