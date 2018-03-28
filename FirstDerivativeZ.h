//
// Created by root on 10/17/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVEZ_H
#define DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVEZ_H


#include "FirstDerivative.h"

class FirstDerivativeZ : public FirstDerivative {
    double calculate(double coord, double t);

public:
    explicit FirstDerivativeZ(InitialData *initialData);

    FirstDerivativeZ();
};


#endif //DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVEZ_H
