//
// Created by root on 10/17/17.
//

#include "FirstDerivativeY.h"

double FirstDerivativeY::calculate(double coord, double t) {
    return getInitialData()->firstDerivativeY(coord, t);
}

FirstDerivativeY::FirstDerivativeY(InitialData *initialData) : FirstDerivative(initialData) {}

FirstDerivativeY::FirstDerivativeY() {};
