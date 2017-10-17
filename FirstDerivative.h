//
// Created by root on 10/17/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVE_H
#define DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVE_H


#include "InitialData.h"

class FirstDerivative {
private:
    InitialData *initialData;
public:
    virtual double calculate(double coord, double t)= 0;

    explicit FirstDerivative(InitialData *initialData);

    FirstDerivative();

    InitialData *getInitialData() const;

    void setInitialData(InitialData *initialData);
};


#endif //DYNAMIC_SYSTEMS_DSL_FIRSTDERIVATIVE_H
