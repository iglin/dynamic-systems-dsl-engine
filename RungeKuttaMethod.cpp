//
// Created by root on 10/22/17.
//

#include "RungeKuttaMethod.h"

PointsTable *RungeKuttaMethod::apply(FirstDerivative *firstDerivative, double y0, double a, double b, double h) {
    double n = (b - a) / h;
    double xArray[(int) n];
    PointsTable *table = new PointsTable();

    table->addPoint(a, y0);
    xArray[0] = a;
    double k1, k2, k3, k4, y;
    for (int i = 1; i <= n; i++) {
        xArray[i] = xArray[i - 1] + h;
        k1 = firstDerivative->calculate(xArray[i - 1], table->getY(xArray[i - 1]));
        k2 = firstDerivative->calculate(xArray[i - 1] + h / 2, table->getY(xArray[i - 1]) + (h / 2) * k1);
        k3 = firstDerivative->calculate(xArray[i - 1] + h / 2, table->getY(xArray[i - 1]) + (h / 2) * k2);
        k4 = firstDerivative->calculate(xArray[i - 1] + h, table->getY(xArray[i - 1]) + h * k3);

        y = table->getY(xArray[i - 1]) + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
        table->addPoint(xArray[i], y);
    }
    return table;
}
