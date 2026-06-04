# Boron Compiler
# Copyright (C) 2026 Samuel Little

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# See <LICENSE> for details.

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