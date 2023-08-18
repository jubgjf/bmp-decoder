cmake_minimum_required(VERSION 3.21)

project(bmp-decoder)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-g -Wall -Wextra)

add_executable(
    decoder
    src/def.h
    src/decoder.c
    src/header.h
    src/header.c
    src/pixel.h
    src/pixel.c
)
