cmake_minimum_required(VERSION 3.16)

project(uWASM C)
set(CMAKE_C_STANDARD 99)

add_library(uWASM
    src/uWASM.c
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
link_libraries(uWASM)

add_executable(uWASMTest 
    ${CMAKE_CURRENT_LIST_DIR}/test/main.c
)