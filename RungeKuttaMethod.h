//
// Created by root on 10/22/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_RUNGEKUTTAMETHOD_H
#define DYNAMIC_SYSTEMS_DSL_RUNGEKUTTAMETHOD_H


#include "FirstDerivative.h"
#include "PointsTable.h"
#include "NumericalMethod.h"

class RungeKuttaMethod : public NumericalMethod {
public:
    Result *apply(InitialData *data, double h) override;
};


#endif //DYNAMIC_SYSTEMS_DSL_RUNGEKUTTAMETHOD_H
