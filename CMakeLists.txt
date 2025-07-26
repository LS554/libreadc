#this is mainly a dummy for jetbrains ide

cmake_minimum_required(VERSION 3.31)
project(libread C)

set(CMAKE_C_STANDARD 11)

add_executable(test
        src/libread.c
        src/test.c

)
