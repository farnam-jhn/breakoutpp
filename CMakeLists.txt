cmake_minimum_required(VERSION 3.10)
project(breakoutpp)

file(GLOB SOURCES
    main.cpp
    includes/*.cpp
)

add_executable(breakoutpp ${SOURCES})
target_include_directories(breakoutpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)
