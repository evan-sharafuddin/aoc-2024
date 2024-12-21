cmake_minimum_required(VERSION 3.10)
project(aoc_2024)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# Add include directories
include_directories(${INCLUDE_DIR})

## Collect all source files
#file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

# Collect all source files
file(GLOB SOURCES "${SRC_DIR}/*.cpp")

# Loop through each source file and create an executable
foreach(SOURCE_FILE ${SOURCES})
    # Get the file name without the directory and extension
    get_filename_component(EXEC_NAME ${SOURCE_FILE} NAME_WE)

    # Create an executable for the source file
    add_executable(${EXEC_NAME} ${SOURCE_FILE})


endforeach()