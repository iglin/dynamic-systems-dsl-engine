//
// Created by root on 10/22/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_RUNGEKUTTAMETHOD_H
#define DYNAMIC_SYSTEMS_DSL_RUNGEKUTTAMETHOD_H


#include "FirstDerivative.h"
#include "PointsTable.h"

class RungeKuttaMethod {
public:
    static PointsTable *apply(FirstDerivative *firstDerivative, double y0, double a, double b, double h);
};


#endif //DYNAMIC_SYSTEMS_DSL_RUNGEKUTTAMETHOD_H
