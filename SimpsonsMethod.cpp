//
// Created by alex on 14.05.18.
//

#include "SimpsonsMethod.h"

Result *SimpsonsMethod::apply(InitialData *data, double h) {
    int n = static_cast<int>(round((data->getTFinal() - data->getT0()) / h));
    if (n % 2 != 0) n++;
    double tArray[n];
    PointsTable *xTable = new PointsTable("x");
    PointsTable *yTable = new PointsTable("y");
    PointsTable *zTable = new PointsTable("z");

#if defined(dx)
    xTable->addPoint(data->getT0(), data->getX0());
#endif
#if defined(dy)
    yTable->addPoint(data->getT0(), data->getY0());
#endif
#if defined(dz)
    zTable->addPoint(data->getT0(), data->getZ0());
#endif

    tArray[0] = data->getT0();

    double b;
    for (int i = 0; i <= n; i++) {
        if (i == 0 || i == n) b = h / 3;
        else if (i % 2 == 0) b = 2 * h / 3;
        else b = 4 * h / 3;
#if defined(dx)
        xTable->addPoint(tArray[i], xTable->getY(tArray[i - 1]) + b * data->firstDerivativeX(0, tArray[i]));
#endif
#if defined(dy)
        yTable->addPoint(tArray[i], yTable->getY(tArray[i - 1]) + b * data->firstDerivativeY(0, tArray[i]));
#endif
#if defined(dz)
        zTable->addPoint(tArray[i], zTable->getY(tArray[i - 1]) + b * data->firstDerivativeZ(0, tArray[i]));
#endif
    }
    return new Result(xTable, yTable, zTable);
}
