# cmake_minimum_required(VERSION <specify CMake version here>)
project(UNIX_projekt)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(UNIX_projekt
        Addons.h
        Lexer.cpp
        Lexer.h
        Parser.cpp
        Parser.h
        Source.cpp
        Source.h Token.cpp Token.h Structs.h)
