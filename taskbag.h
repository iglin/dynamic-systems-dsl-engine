//
// Created by alex on 15.05.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TASKBAG_H
#define DYNAMIC_SYSTEMS_DSL_TASKBAG_H


#include "InitialData.h"
#include "templet.hpp"
#include "Result.h"
#include "NumericalMethod.h"


class TempletProxy {
public:
    Result *runTempletEngine(NumericalMethod *method, InitialData *initialData, double hBase, int M);

    int N;
    int M;
    double *T_ARRAY;
    double *H;
    double H_BASE;
    double **TX;
    double **TY;
    double **TZ;
    InitialData *iDATA;
    PointsTable *X_TABLE;
    PointsTable *Y_TABLE;
    PointsTable *Z_TABLE;
    NumericalMethod *METHOD;
};

#endif //DYNAMIC_SYSTEMS_DSL_TASKBAG_H
