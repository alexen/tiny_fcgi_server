cmake_minimum_required(VERSION 3.15)

project(tiny_fcgi_server)

add_definitions(-std=c++17)
add_definitions(-Wall -Werror -Wpedantinc -Wextra)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -fno-inline")