//
// Created by root on 10/13/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_EULERSMETHOD_H
#define DYNAMIC_SYSTEMS_DSL_EULERSMETHOD_H


#include "PointsTable.h"

class EulersMethod {
public:
    static PointsTable *apply(double (*firstDerivative)(double, double), double a, double b, double h);
    //static PointsTable *apply(double &firstDerivative(double, double), double a, double b, double h);
};


#endif //DYNAMIC_SYSTEMS_DSL_EULERSMETHOD_H
