//
// Created by alex on 11.05.18.
//

#include "Result.h"
#include "InitialData.h"

#ifndef DYNAMIC_SYSTEMS_DSL_NUMERICALMETHOD_H
#define DYNAMIC_SYSTEMS_DSL_NUMERICALMETHOD_H

class NumericalMethod {
public:
    virtual Result *apply(InitialData *data, double h) = 0;

    virtual double calculateNextX(double xPrev, double yPrev, double zPrev, double tPrev, double h) = 0;

    virtual double calculateNextY(double xPrev, double yPrev, double zPrev, double tPrev, double h) = 0;

    virtual double calculateNextZ(double xPrev, double yPrev, double zPrev, double tPrev, double h) = 0;
};

#endif //DYNAMIC_SYSTEMS_DSL_NUMERICALMETHOD_H
