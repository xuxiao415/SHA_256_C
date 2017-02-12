cmake_minimum_required(VERSION 3.6)
project(SHA_256_C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES utils.c)
add_executable(SHA_256_C ${SOURCE_FILES})