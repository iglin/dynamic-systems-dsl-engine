//
// Created by alex on 08.05.18.
//

#include "HeunsMethod.h"

//PointsTable *HeunsMethod::applyPolynomical(FirstDerivative *firstDerivative, double y0, double a, double b, double h) {
//    double n = (b - a) / h;
//    double xArray[(int) n];
//    PointsTable *table = new PointsTable();
//
//    table->addPoint(a, y0);
//    xArray[0] = a;
//    double yPrev, intermediateValue, y;
//    for (int i = 1; i <= n; i++) {
//        yPrev = table->getY(xArray[i - 1]);
//        intermediateValue = table->getY(xArray[i - 1]) + h * firstDerivative->calculate(xArray[i - 1], yPrev);
//        xArray[i] = xArray[i - 1] + h;
//        y = yPrev + (h / 2.0d) * (firstDerivative->calculate(xArray[i - 1], yPrev) + firstDerivative->calculate(xArray[i], intermediateValue));
//        table->addPoint(xArray[i], y);
//    }
//    return table;
//}

Result *HeunsMethod::apply(InitialData *data, double h) {
    return nullptr;
}
