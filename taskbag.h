//
// Created by alex on 15.05.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_TASKBAG_H
#define DYNAMIC_SYSTEMS_DSL_TASKBAG_H


#include "InitialData.h"
#include "templet.hpp"


class Taskbag {
public:
    int runTempletEngine(InitialData *initialData, double hBase);
private:
    const int PROC_NUM = 16;
    const int M = PROC_NUM / 2;
    double *T_ARRAY = nullptr;
    double *H = nullptr;
    double **TET_TX = nullptr;
    double **TET_TY = nullptr;
    InitialData *iDATA = nullptr;
};

#endif //DYNAMIC_SYSTEMS_DSL_TASKBAG_H
