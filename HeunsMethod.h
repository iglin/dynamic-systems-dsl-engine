//
// Created by alex on 08.05.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_HEUNSMETHOD_H
#define DYNAMIC_SYSTEMS_DSL_HEUNSMETHOD_H


#include "PointsTable.h"
#include "NumericalMethod.h"

class HeunsMethod : NumericalMethod {
public:
private:
    Result *apply(InitialData *data, double h) override;
};


#endif //DYNAMIC_SYSTEMS_DSL_HEUNSMETHOD_H
