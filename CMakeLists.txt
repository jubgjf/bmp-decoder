cmake_minimum_required(VERSION 3.21)

project(bmp-decoder)

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