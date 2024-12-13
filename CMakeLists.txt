cmake_minimum_required(VERSION 3.16)

project(MySDLProject VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(my_sdl_project src/main.c)

target_include_directories(my_sdl_project PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(my_sdl_project PRIVATE ${SDL2_LIBRARIES})