#this is mainly a dummy for jetbrains ide, use makefile `src/library.mak` to compile library

cmake_minimum_required(VERSION 3.31)
project(libread C)

set(CMAKE_C_STANDARD 11)

add_executable(test
        src/libreadc.c
        example.c

)
