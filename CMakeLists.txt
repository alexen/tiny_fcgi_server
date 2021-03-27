cmake_minimum_required(VERSION 3.15)

project(tiny_fcgi_server)

add_definitions(-std=c++17)
add_definitions(-Wall -Werror -Wpedantic -Wextra)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -fno-inline")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(Fcgi REQUIRED)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(server)