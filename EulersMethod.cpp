//
// Created by root on 10/13/17.
//

#include <cstdlib>
#include "EulersMethod.h"
#include "Result.h"

using namespace std;

Result *EulersMethod::apply(InitialData *initialData, double h) {
    int n = static_cast<int>(round((initialData->getTFinal() - initialData->getT0()) / h));
    double tArray[n];
    PointsTable *xTable = new PointsTable("x");
    PointsTable *yTable = new PointsTable("y");
    PointsTable *zTable = new PointsTable("z");

#if defined(dx)
    xTable->addPoint(initialData->getT0(), initialData->getX0());
#endif
#if defined(dy)
    yTable->addPoint(initialData->getT0(), initialData->getY0());
#endif
#if defined(dz)
    zTable->addPoint(initialData->getT0(), initialData->getZ0());
#endif
    tArray[0] = initialData->getT0();
    double value;
    for (int i = 1; i < n; i++) {
        tArray[i] = tArray[i - 1] + h;
#if defined(dx)
#if defined(dy)
#if defined(dz)
        value = xTable->getY(tArray[i - 1]) + h
                * initialData->firstDerivativeX(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]),
                                              tArray[i - 1]);
        xTable->addPoint(tArray[i], value);

        value = yTable->getY(tArray[i - 1]) + h
                * initialData->firstDerivativeY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]),
                                              tArray[i - 1]);
        yTable->addPoint(tArray[i], value);

        value = zTable->getY(tArray[i - 1]) + h
                * initialData->firstDerivativeZ(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]),
                                              tArray[i - 1]);
        zTable->addPoint(tArray[i], value);
#else
        value = xTable->getY(tArray[i - 1]) + h * initialData->firstDerivativeX(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]),
                                                                              tArray[i - 1]);
        xTable->addPoint(tArray[i], value);

        value = yTable->getY(tArray[i - 1]) + h * initialData->firstDerivativeY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]),
                                                                              tArray[i - 1]);
        yTable->addPoint(tArray[i], value);
#endif
#else
        value = xTable->getY(tArray[i - 1]) + h * initialData->firstDerivativeX(xTable->getY(tArray[i - 1]), tArray[i - 1]);
        xTable->addPoint(tArray[i], value);
#endif
#endif
    }
    return new Result(xTable, yTable, zTable);
}

double EulersMethod::calculateNextX(double xPrev, double yPrev, double zPrev, double tPrev, double h) {
    return xPrev + h * InitialData::derivativeX(xPrev, yPrev, zPrev, tPrev);
}

double EulersMethod::calculateNextY(double xPrev, double yPrev, double zPrev, double tPrev, double h) {
    return yPrev + h * InitialData::derivativeY(xPrev, yPrev, zPrev, tPrev);
}

double EulersMethod::calculateNextZ(double xPrev, double yPrev, double zPrev, double tPrev, double h) {
    return zPrev + h * InitialData::derivativeZ(xPrev, yPrev, zPrev, tPrev);
}
