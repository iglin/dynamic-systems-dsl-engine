//
// Created by root on 10/17/17.
//

#include "FirstDerivativeZ.h"

double FirstDerivativeZ::calculate(double coord, double t) {
    return getInitialData()->firstDerivativeZ(coord, t);
}

FirstDerivativeZ::FirstDerivativeZ(InitialData *initialData) : FirstDerivative(initialData) {}

FirstDerivativeZ::FirstDerivativeZ() = default;
