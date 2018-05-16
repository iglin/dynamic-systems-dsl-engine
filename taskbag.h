//
// Created by alex on 15.05.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TASKBAG_H
#define DYNAMIC_SYSTEMS_DSL_TASKBAG_H


#include "InitialData.h"
#include "templet.hpp"
#include "Result.h"


class Taskbag {
public:
    Result *runTempletEngine(InitialData *initialData, double hBase);

    const int PROC_NUM = 8;
    //const int M = PROC_NUM / 2;
    const int M = PROC_NUM;
    int N;
    double *T_ARRAY;
    double *H;
    double H_BASE;
    double **TET_TX;
    double **TET_TY;
    InitialData *iDATA;
    PointsTable *X_TABLE;
    PointsTable *Y_TABLE;
};

#endif //DYNAMIC_SYSTEMS_DSL_TASKBAG_H
