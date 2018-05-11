//
// Created by root on 10/17/17.
//

#include "FirstDerivativeZ.h"

double FirstDerivativeZ::calculate(double x, double y, double z, double t) {
    return getInitialData()->firstDerivativeZ(x, y, z, t);
}

FirstDerivativeZ::FirstDerivativeZ(InitialData *initialData) : FirstDerivative(initialData) {}

FirstDerivativeZ::FirstDerivativeZ() = default;
