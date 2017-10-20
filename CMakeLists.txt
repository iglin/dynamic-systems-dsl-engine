cmake_minimum_required(VERSION 3.8)
project(dynamic_systems_dsl)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fopenmp")

set(SOURCE_FILES main.cpp EulersMethod.cpp EulersMethod.h InitialData.cpp InitialData.h PointsTable.cpp PointsTable.h FirstDerivative.cpp FirstDerivative.h FirstDerivativeX.cpp FirstDerivativeX.h FirstDerivativeY.cpp FirstDerivativeY.h FirstDerivativeZ.cpp FirstDerivativeZ.h)
add_executable(dynamic_systems_dsl ${SOURCE_FILES})