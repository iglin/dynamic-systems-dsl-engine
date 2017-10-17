//
// Created by root on 10/13/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_EULERSMETHOD_H
#define DYNAMIC_SYSTEMS_DSL_EULERSMETHOD_H


#include "PointsTable.h"
#include "FirstDerivative.h"

class EulersMethod {
public:
    /* Through method ref, doesn't work
    static PointsTable *apply(double (*firstDerivative)(double, double), double a, double b, double h);
    //static PointsTable *apply(double &firstDerivative(double, double), double a, double b, double h);
    */

    static PointsTable *apply(FirstDerivative *firstDerivative, double a, double b, double h);
};


#endif //DYNAMIC_SYSTEMS_DSL_EULERSMETHOD_H
