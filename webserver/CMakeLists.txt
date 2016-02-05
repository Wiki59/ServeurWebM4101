cmake_minimum_required(VERSION 3.3)
project(webserver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.c
    Makefile)

add_executable(webserver ${SOURCE_FILES})