cmake_minimum_required(VERSION 3.5)
project(minmaxheap)
set(CMAKE_CXX_FLAGS "-std=c++14 -ggdb -g -Wall -Wextra")

add_subdirectory(/home/wojtek/Downloads/googletest binary_dir EXCLUDE_FROM_ALL)

enable_testing()

add_executable(runUnitTests
    minmaxheap_test.cpp)

target_link_libraries(runUnitTests gtest gtest_main pthread)

add_test(
    NAME runUnitTests
    COMMAND runUnitTests --gtest_color=yes)
