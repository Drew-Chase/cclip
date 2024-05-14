cmake_minimum_required(VERSION 3.5.0)
project(cclip VERSION 0.0.6)
project(cclip-example VERSION 0.0.6)
set(CMAKE_CXX_STANDARD 17)

add_library(cclip STATIC
        includes/option.h
        src/options_manager.cpp
        includes/options_manager.h)
add_executable(cclip-example example/main.cpp)
target_link_libraries(cclip-example cclip)

target_include_directories(cclip PUBLIC includes)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES INTERMEDIATE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/obj/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "-debug")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")