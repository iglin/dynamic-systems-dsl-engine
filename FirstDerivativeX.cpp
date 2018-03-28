//
// Created by root on 10/17/17.
//

#include "FirstDerivativeX.h"

double FirstDerivativeX::calculate(double coord, double t) {
    return getInitialData()->firstDerivativeX(coord, t);
}

FirstDerivativeX::FirstDerivativeX() {};

FirstDerivativeX::FirstDerivativeX(InitialData *initialData) : FirstDerivative(initialData) {}
