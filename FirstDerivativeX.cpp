//
// Created by root on 10/17/17.
//

#include "FirstDerivativeX.h"

double FirstDerivativeX::calculate(double x, double y, double z, double t) {
    return getInitialData()->firstDerivativeX(x, y, z, t);
}

FirstDerivativeX::FirstDerivativeX() = default;

FirstDerivativeX::FirstDerivativeX(InitialData *initialData) : FirstDerivative(initialData) {}
