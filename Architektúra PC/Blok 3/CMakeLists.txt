cmake_minimum_required(VERSION 3.27)
project(Blok_3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Blok_3 blok3.c)

target_link_libraries(Blok_3 ws2_32)
