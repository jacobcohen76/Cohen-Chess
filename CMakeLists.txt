cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_COMPILER clang++-14)#g++-11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fconstexpr-steps=2147483647")#"-fconstexpr-ops-limit=2147483647 -march=native")#"-fconstexpr-steps=2147483647")" # -Wall -Wpedantic -Wshadow
project(Cohen-Chess)
include_directories(include)
add_subdirectory(src)