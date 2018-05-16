//
// Created by alex on 14.05.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_POLYNOMICALEXTRAPOLATION_H
#define DYNAMIC_SYSTEMS_DSL_POLYNOMICALEXTRAPOLATION_H


#include "Result.h"
#include "InitialData.h"
#include "NumericalMethod.h"

class Extrapolation {
public:
    Result *applyPolynomical(InitialData *initialData, double H, int M);

    Result *applyRational(InitialData *initialData, double H, int M);

    Result *applyRationalParallel(NumericalMethod *method, InitialData *initialData, double H);
};


#endif //DYNAMIC_SYSTEMS_DSL_POLYNOMICALEXTRAPOLATION_H
