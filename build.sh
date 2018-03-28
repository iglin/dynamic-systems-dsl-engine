#!/usr/bin/env bash
mkdir ./target
chmod a+x run.sh
g++ -fopenmp -Wall -otarget/sortchain-`uname -m` main.cpp EulersMethod.cpp EulersMethod.h InitialData.cpp InitialData.h PointsTable.cpp PointsTable.h FirstDerivative.cpp FirstDerivative.h FirstDerivativeX.cpp FirstDerivativeX.h FirstDerivativeY.cpp FirstDerivativeY.h FirstDerivativeZ.cpp FirstDerivativeZ.h RungeKuttaMethod.cpp RungeKuttaMethod.h



