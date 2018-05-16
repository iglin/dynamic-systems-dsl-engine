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
    Result *applyPolynomical(NumericalMethod *method, InitialData *initialData, double H, int M);

    Result *applyRational(NumericalMethod *method, InitialData *initialData, double H, int M);

    Result *applyRationalOMP(NumericalMethod *method, InitialData *initialData, double H, int M);

    Result *applyRationalParallel(NumericalMethod *method, InitialData *initialData, double H);
};


#endif //DYNAMIC_SYSTEMS_DSL_POLYNOMICALEXTRAPOLATION_H
