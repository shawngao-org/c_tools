cmake_minimum_required(VERSION 3.27)
project(tools_debug C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/usr/local/include")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/usr/local/lib")

add_executable(tools_debug main.c)

target_link_libraries(tools_debug tools)
