//
// Created by alex on 14.05.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_POLYNOMICALEXTRAPOLATION_H
#define DYNAMIC_SYSTEMS_DSL_POLYNOMICALEXTRAPOLATION_H


#include "Result.h"
#include "InitialData.h"

class Extrapolation {
public:
    Result *applyPolynomical(InitialData *initialData, double H, int M);

    Result *applyRational(InitialData *initialData, double H, int M);
};


#endif //DYNAMIC_SYSTEMS_DSL_POLYNOMICALEXTRAPOLATION_H
