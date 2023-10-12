# CMake options
cmake_minimum_required(VERSION 3.26)
project(CCommandLineParser)
set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Library
add_library(CCommandLineParser src/options_manager.cpp src/options_manager.h)
add_executable(CCommandLineParserTest test-src/main.cpp)
target_link_libraries(CCommandLineParserTest CCommandLineParser)