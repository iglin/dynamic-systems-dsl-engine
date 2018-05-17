//
// Created by alex on 16.05.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_DORMANDPRINCEMETHOD_H
#define DYNAMIC_SYSTEMS_DSL_DORMANDPRINCEMETHOD_H


#include "NumericalMethod.h"


class DormandPrinceMethod : public NumericalMethod {
public:
    Result *apply(InitialData *data, double h);

    double calculateNextX(double xPrev, double yPrev, double zPrev, double tPrev, double h);

    double calculateNextY(double xPrev, double yPrev, double zPrev, double tPrev, double h);

    double calculateNextZ(double xPrev, double yPrev, double zPrev, double tPrev, double h);
};


#endif //DYNAMIC_SYSTEMS_DSL_DORMANDPRINCEMETHOD_H
