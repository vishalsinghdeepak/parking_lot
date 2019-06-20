cmake_minimum_required(VERSION 3.7)
project(gojak)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Global_declaration.h Formatting.h Command_function.h File_mode.h Console_mode.h)
add_executable(gojak ${SOURCE_FILES})