cmake_minimum_required(VERSION 3.7)
project(Library)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c books.c books.h)
add_executable(Library ${SOURCE_FILES})