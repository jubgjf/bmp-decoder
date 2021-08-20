cmake_minimum_required(VERSION 3.21)

project(bmp-decoder)

add_compile_options(-Wall -Wextra)

add_executable(
    decoder
    src/decoder.c
    src/header.h
    src/header.c
)