//
// Created by root on 10/13/17.
//

#include <cstdlib>
#include "EulersMethod.h"
#include "Result.h"

using namespace std;

Result *EulersMethod::apply(InitialData *initialData, double h) {
    int n = static_cast<int>(round((initialData->getTFinal() - initialData->getT0()) / h));
    double tArray[(int) n];
    PointsTable *xTable = new PointsTable();
    PointsTable *yTable = new PointsTable();
    PointsTable *zTable = new PointsTable();

    xTable->addPoint(initialData->getT0(), initialData->getX0());
    xTable->addPoint(initialData->getT0(), initialData->getY0());
    xTable->addPoint(initialData->getT0(), initialData->getZ0());
    tArray[0] = initialData->getT0();
    double value;
    for (int i = 1; i < n; i++) {
        tArray[i] = tArray[i - 1] + h;
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
    }
    return new Result(xTable, yTable, zTable);
}
