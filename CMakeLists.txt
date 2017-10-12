cmake_minimum_required(VERSION 3.8)
project(dynamic_systems_dsl)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp EulersMethod.cpp EulersMethod.h FirstDerivative2D.cpp FirstDerivative2D.h FunctionParser.cpp FunctionParser.h)
add_executable(dynamic_systems_dsl ${SOURCE_FILES})