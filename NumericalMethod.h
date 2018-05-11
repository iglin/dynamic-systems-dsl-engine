//
// Created by alex on 11.05.18.
//

#include "Result.h"
#include "InitialData.h"

#ifndef DYNAMIC_SYSTEMS_DSL_NUMERICALMETHOD_H
#define DYNAMIC_SYSTEMS_DSL_NUMERICALMETHOD_H

#endif //DYNAMIC_SYSTEMS_DSL_NUMERICALMETHOD_H

class NumericalMethod {
public:
    virtual Result *apply(InitialData *data, double h) = 0;
};
