//
// Created by alex on 14.05.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_SIMSONSMETHOD_H
#define DYNAMIC_SYSTEMS_DSL_SIMSONSMETHOD_H


#include "NumericalMethod.h"

class SimpsonsMethod : NumericalMethod {
public:
    Result *apply(InitialData *data, double h);
};


#endif //DYNAMIC_SYSTEMS_DSL_SIMSONSMETHOD_H
