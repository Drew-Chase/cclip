cmake_minimum_required(VERSION 3.0.0)
project(cclip VERSION 0.0.5)
project(cclip-example VERSION 0.0.5)
set(CMAKE_CXX_STANDARD 17)

add_library(cclip INTERFACE)
add_executable(cclip-example example/main.cpp)
target_link_libraries(cclip-example cclip)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES INTERMEDIATE_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/obj/${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "-debug")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")