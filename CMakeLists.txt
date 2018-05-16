cmake_minimum_required(VERSION 3.8)
project(dynamic_systems_dsl)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fopenmp")

set(SOURCE_FILES main.cpp taskbag.cpp taskbag.h templet.hpp EulersMethod.cpp EulersMethod.h InitialData.cpp InitialData.h
        PointsTable.cpp PointsTable.h RungeKuttaMethod.cpp RungeKuttaMethod.h ExportUtils.cpp ExportUtils.h HeunsMethod.cpp
        HeunsMethod.h Result.cpp Result.h NumericalMethod.h SimpsonsMethod.cpp SimpsonsMethod.h Extrapolation.cpp Extrapolation.h)
add_executable(dynamic_systems_dsl ${SOURCE_FILES})