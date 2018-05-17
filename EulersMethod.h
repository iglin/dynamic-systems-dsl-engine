//
// Created by root on 10/13/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_EULERSMETHOD_H
#define DYNAMIC_SYSTEMS_DSL_EULERSMETHOD_H


#include "PointsTable.h"
#include "Result.h"
#include "NumericalMethod.h"

class EulersMethod : public NumericalMethod {
public:
    Result *apply(InitialData *data, double h);

    double calculateNextX(double xPrev, double yPrev, double zPrev, double tPrev, double h);

    double calculateNextY(double xPrev, double yPrev, double zPrev, double tPrev, double h);

    double calculateNextZ(double xPrev, double yPrev, double zPrev, double tPrev, double h);
};


#endif //DYNAMIC_SYSTEMS_DSL_EULERSMETHOD_H
