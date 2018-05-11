//
// Created by root on 10/17/17.
//

#include "FirstDerivativeY.h"

double FirstDerivativeY::calculate(double x, double y, double z, double t) {
    return getInitialData()->firstDerivativeY(x, y, z, t);
}

FirstDerivativeY::FirstDerivativeY(InitialData *initialData) : FirstDerivative(initialData) {}

FirstDerivativeY::FirstDerivativeY() = default;
