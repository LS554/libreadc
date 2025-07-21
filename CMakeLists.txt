cmake_minimum_required(VERSION 3.31)
project(libread C)

set(CMAKE_C_STANDARD 11)

add_executable(libread main.c
        libread.h
        test.c)
