//
// Created by alex on 14.05.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_POLYNOMICALEXTRAPOLATION_H
#define DYNAMIC_SYSTEMS_DSL_POLYNOMICALEXTRAPOLATION_H


#include "Result.h"
#include "InitialData.h"
#include "NumericalMethod.h"
#include "DormandPrinceMethod.h"

class Extrapolation {
public:
    Result *applyPolynomical(DormandPrinceMethod *method, InitialData *initialData, double H, int M);

    Result *applyRational(DormandPrinceMethod *method, InitialData *initialData, double H, int M);

    Result *applyRationalOMP(DormandPrinceMethod *method, InitialData *initialData, double H, int M);

    Result *applyRationalParallel(DormandPrinceMethod *method, InitialData *initialData, double H, int M);
};


#endif //DYNAMIC_SYSTEMS_DSL_POLYNOMICALEXTRAPOLATION_H
