cmake_minimum_required(VERSION 3.16)

project(uWASM C)
set(C_STANDARD 99)

add_library(${PROJECT_NAME}
    src/uWASM.c
)

target_include_directories(${PROJECT_NAME} PUBLIC include)

project(uWASMTest C)
set(C_STANDARD 99)

add_executable(${PROJECT_NAME}
    test/main.c
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} uWASM)
