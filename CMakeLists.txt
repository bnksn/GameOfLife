cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GameOfLife)

add_library(GameOfLifeLib
    STATIC 
    src/gameOfLife.cpp 
)

add_executable(GameOfLife
    src/main.cpp 
)

target_link_libraries(GameOfLife PRIVATE GameOfLifeLib) 

add_compile_options(-Wall -Wextra -pedantic -Werror -Wconversion -O3)