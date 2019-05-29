cmake_minimum_required(VERSION 3.14)
project(transferHB)

set(CMAKE_CXX_STANDARD 14)

add_executable(transferHB main.cpp Storage.cpp Storage.h Weight.h HoogieBoogie.cpp HoogieBoogie.h Terminal.cpp Terminal.h TerminalException.h)