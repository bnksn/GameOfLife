cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_CLANG_TIDY 
    clang-tidy;
        -checks=cppcoreguidelines-*,-cppcoreguidelines-avoid-magic-numbers,-cppcoreguidelines-non-private-member-variables-in-classes,modernize-*,-modernize-use-trailing-return-type,bugprone-*,-bugprone-easily-swappable-parameters;
        -warnings-as-errors=*;
        -header-filter=.*;)

project(GameOfLife)

add_executable(GameOfLife
    src/gameOfLife.cpp 
)

add_compile_options(-Wall -Wextra -pedantic -Werror -Wconversion -O3)