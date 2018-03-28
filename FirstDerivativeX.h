//
// Created by root on 10/17/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVEX_H
#define DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVEX_H


#include "FirstDerivative.h"

class FirstDerivativeX : public FirstDerivative {
    double calculate(double coord, double t);

public:
    explicit FirstDerivativeX(InitialData *initialData);

    FirstDerivativeX();
};


#endif //DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVEX_H
