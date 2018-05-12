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
        value = xTable->getY(tArray[i - 1]) + h
                * initialData->firstDerivativeX(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]),
                                              tArray[i - 1]);
        xTable->addPoint(tArray[i], value);
#endif
#if defined(dy)
        value = yTable->getY(tArray[i - 1]) + h
                * initialData->firstDerivativeY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]),
                                              tArray[i - 1]);
        yTable->addPoint(tArray[i], value);
#endif
#if defined(dz)
        value = zTable->getY(tArray[i - 1]) + h
                * initialData->firstDerivativeZ(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]),
                                              tArray[i - 1]);
        zTable->addPoint(tArray[i], value);
#endif
    }
    return new Result(xTable, yTable, zTable);
}
