//
// Created by alex on 08.05.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_HEUNSMETHOD_H
#define DYNAMIC_SYSTEMS_DSL_HEUNSMETHOD_H


#include "PointsTable.h"
#include "FirstDerivative.h"

class HeunsMethod {
public:
    static PointsTable *apply(FirstDerivative *firstDerivative, double y0, double a, double b, double h);
};


#endif //DYNAMIC_SYSTEMS_DSL_HEUNSMETHOD_H
