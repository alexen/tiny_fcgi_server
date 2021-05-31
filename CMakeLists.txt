cmake_minimum_required(VERSION 3.15)

project(tiny_fcgi_server)

add_definitions(-std=c++17)
add_definitions(-Wall -Werror -Wpedantic -Wextra)

option(BUILD_SHARED_LIBS "Enable shared libs building by default" ON)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -fno-inline")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(Fcgi REQUIRED)
include_directories(SYSTEM ${Fcgi_INCLUDE_DIRS})

find_package(Boost REQUIRED unit_test_framework)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

find_package(CURL REQUIRED)
include_directories(SYSTEM ${CURL_INCLUDE_DIRS})

find_package(RapidJson REQUIRED)
include_directories(${RapidJson_INCLUDE_DIR})

include(CTest)
enable_testing()

add_subdirectory(server)
add_subdirectory(tools)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} server)
