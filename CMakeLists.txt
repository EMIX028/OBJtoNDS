cmake_minimum_required(VERSION 3.20)

project(OBJtoNDS LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(OBJtoNDS
    src/main.c
)

target_include_directories(OBJtoNDS PRIVATE
    include
)

target_compile_options(OBJtoNDS PRIVATE
    -Wall
    -Wextra
    -Wconversion
    -Werror
    -Wpedantic
    -Wwrite-strings
    -O2
)