cmake_minimum_required(VERSION 3.16)
project(compiler CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(boron ${SOURCES})

target_include_directories(boron PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
)

target_compile_options(boron PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)