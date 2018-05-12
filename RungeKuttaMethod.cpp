//
// Created by root on 10/22/17.
//

#include <iostream>
#include "RungeKuttaMethod.h"


Result *RungeKuttaMethod::apply(InitialData *data, double h) {
    int n = static_cast<int>(round((data->getTFinal() - data->getT0()) / h));
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
    double k1, k2, k3, k4, value;
    for (int i = 1; i < n; i++) {
        tArray[i] = tArray[i - 1] + h;

#if defined(dx)
#if defined(dy)
#if defined(dz)
        k1 = data->firstDerivativeX(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]), tArray[i - 1]);
        k2 = data->firstDerivativeX(xTable->getY(tArray[i - 1]) + (h / 2) * k1, yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]), tArray[i - 1] + h / 2);
        k3 = data->firstDerivativeX(xTable->getY(tArray[i - 1]) + (h / 2) * k2, yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]), tArray[i - 1] + h / 2);
        k4 = data->firstDerivativeX(xTable->getY(tArray[i - 1]) + h * k3, yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]), tArray[i - 1] + h);
        value = xTable->getY(tArray[i - 1]) + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        xTable->addPoint(tArray[i], value);

        k1 = data->firstDerivativeY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]), tArray[i - 1]);
        k2 = data->firstDerivativeY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]) + (h / 2) * k1, zTable->getY(tArray[i - 1]), tArray[i - 1] + h / 2);
        k3 = data->firstDerivativeY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]) + (h / 2) * k2, zTable->getY(tArray[i - 1]), tArray[i - 1] + h / 2);
        k4 = data->firstDerivativeY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]) + h * k3, zTable->getY(tArray[i - 1]), tArray[i - 1] + h);
        value = yTable->getY(tArray[i - 1]) + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        yTable->addPoint(tArray[i], value);

        k1 = data->firstDerivativeZ(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]), tArray[i - 1]);
        k2 = data->firstDerivativeZ(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]) + (h / 2) * k1, tArray[i - 1] + h / 2);
        k3 = data->firstDerivativeZ(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]) + (h / 2) * k2, tArray[i - 1] + h / 2);
        k4 = data->firstDerivativeZ(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]) + h * k3, tArray[i - 1] + h);
        value = zTable->getY(tArray[i - 1]) + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        zTable->addPoint(tArray[i], value);
#else
        k1 = data->firstDerivativeX(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), tArray[i - 1]);
        k2 = data->firstDerivativeX(xTable->getY(tArray[i - 1]) + (h / 2) * k1, yTable->getY(tArray[i - 1]), tArray[i - 1] + h / 2);
        k3 = data->firstDerivativeX(xTable->getY(tArray[i - 1]) + (h / 2) * k2, yTable->getY(tArray[i - 1]), tArray[i - 1] + h / 2);
        k4 = data->firstDerivativeX(xTable->getY(tArray[i - 1]) + h * k3, yTable->getY(tArray[i - 1]), tArray[i - 1] + h);
        value = xTable->getY(tArray[i - 1]) + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        xTable->addPoint(tArray[i], value);

        k1 = data->firstDerivativeY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), tArray[i - 1]);
        k2 = data->firstDerivativeY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]) + (h / 2) * k1, tArray[i - 1] + h / 2);
        k3 = data->firstDerivativeY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]) + (h / 2) * k2, tArray[i - 1] + h / 2);
        k4 = data->firstDerivativeY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]) + h * k3, tArray[i - 1] + h);
        value = yTable->getY(tArray[i - 1]) + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        yTable->addPoint(tArray[i], value);
#endif
#else
        k1 = data->firstDerivativeX(xTable->getY(tArray[i - 1]), tArray[i - 1]);
        k2 = data->firstDerivativeX(xTable->getY(tArray[i - 1]) + (h / 2) * k1, tArray[i - 1] + h / 2);
        k3 = data->firstDerivativeX(xTable->getY(tArray[i - 1]) + (h / 2) * k2, tArray[i - 1] + h / 2);
        k4 = data->firstDerivativeX(xTable->getY(tArray[i - 1]) + h * k3, tArray[i - 1] + h);
        value = xTable->getY(tArray[i - 1]) + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        xTable->addPoint(tArray[i], value);
#endif
#endif
        }
    return new Result(xTable, yTable, zTable);
}
