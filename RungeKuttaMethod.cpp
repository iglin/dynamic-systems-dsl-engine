//
// Created by root on 10/22/17.
//

#include "RungeKuttaMethod.h"


Result *RungeKuttaMethod::apply(InitialData *data, double h) {
    int n = static_cast<int>(round((data->getTFinal() - data->getT0()) / h));
    double tArray[n];
    PointsTable *xTable = new PointsTable();
    PointsTable *yTable = new PointsTable();
    PointsTable *zTable = new PointsTable();
    xTable->addPoint(data->getT0(), data->getX0());
    yTable->addPoint(data->getT0(), data->getY0());
    zTable->addPoint(data->getT0(), data->getZ0());
    tArray[0] = data->getT0();
    double k1, k2, k3, k4, value;
    for (int i = 1; i < n; i++) {
        tArray[i] = tArray[i - 1] + h;

        k1 = data->firstDerivativeX(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]), tArray[i - 1]);
        k2 = data->firstDerivativeX(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]), tArray[i - 1] + h / 2);
        k2 = firstDerivative->calculate(tArray[i - 1] + h / 2, xTable->getY(tArray[i - 1]) + (h / 2) * k1);
        k3 = firstDerivative->calculate(tArray[i - 1] + h / 2, xTable->getY(tArray[i - 1]) + (h / 2) * k2);

        value = xTable->getY(tArray[i - 1]) + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        xTable->addPoint(tArray[i], value);
    }
    return table;
}
