cmake_minimum_required(VERSION 3.5.0)
project(cclip VERSION 0.1.0)
project(cclip-example VERSION 0.0.6)
set(CMAKE_CXX_STANDARD 17)

add_library(cclip INTERFACE)
target_include_directories(cclip INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(cclip PROPERTIES LINKER_LANGUAGE CXX)

# Example project
add_executable(cclip-example example/main.cpp)

set_target_properties(cclip-example PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME}")
set_target_properties(cclip-example PROPERTIES INTERMEDIATE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/obj/${PROJECT_NAME}")
set_target_properties(cclip-example PROPERTIES DEBUG_POSTFIX "-debug")
set_target_properties(cclip-example PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")