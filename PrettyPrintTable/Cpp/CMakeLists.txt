cmake_minimum_required(VERSION 3.23)
project(PrettyPrintCpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(PrettyPrintCpp
        PrettyPrintCpp.h
        PrettyPrintCpp.h IterPair.h main.cpp)