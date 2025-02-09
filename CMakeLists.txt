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

enable_testing()

find_package(GTest REQUIRED)

add_library(GameOfLifeLib
    STATIC 
    src/gameOfLife.cpp 
)

add_executable(GameOfLife
    src/main.cpp 
)

target_link_libraries(GameOfLife PRIVATE GameOfLifeLib) 

add_executable(GameOfLifeTests 
    tests/main.cpp 
    tests/gameOfLifeTests.cpp 
)

target_link_libraries(GameOfLifeTests PRIVATE GTest::gtest GameOfLifeLib)

add_test(NAME GameOfLifeTests
         COMMAND $<TARGET_FILE:GameOfLifeTests>)

add_compile_options(-Wall -Wextra -pedantic -Werror -Wconversion -O3)