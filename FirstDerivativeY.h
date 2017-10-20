//
// Created by root on 10/17/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVEY_H
#define DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVEY_H


#include "FirstDerivative.h"

class FirstDerivativeY : public FirstDerivative {
    double calculate(double coord, double t) override;

public:
    explicit FirstDerivativeY(InitialData *initialData);

    FirstDerivativeY();
};


#endif //DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVEY_H
