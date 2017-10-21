//
// Created by root on 10/13/17.
//

#include <cstdlib>
#include "EulersMethod.h"

using namespace std;

/* Through method ref, doesn't work
static PointsTable *EulersMethod::apply(double (*firstDerivative)(double, double), double a, double b, double h) {
//static PointsTable *EulersMethod::apply(double &firstDerivative(double, double), double a, double b, double h) {
    double n = (b - a) / h;
    double xArray[(int) n];
    auto table = new PointsTable();


    table->addPoint(a, y0);
    //xArray[0] = a; yArray[0] = y0;
    for (int i = 1; i <= n; i++) {
        xArray[i] = a + i * h;
        double y = table->getY(xArray[i - 1]) + h * (*firstDerivative)(xArray[i - 1], table->getY(xArray[i - 1]));
        table->addPoint(xArray[i], y);
    }
    return table;
}*/

PointsTable *EulersMethod::apply(FirstDerivative *firstDerivative, double y0, double a, double b, double h) {
    double n = (b - a) / h;
    double xArray[(int) n];
    auto table = new PointsTable();

    table->addPoint(a, y0);
    xArray[0] = a;
    for (int i = 1; i <= n; i++) {
        xArray[i] = xArray[i - 1] + h;
        double y = table->getY(xArray[i - 1]) + h * firstDerivative->calculate(xArray[i - 1], table->getY(xArray[i - 1]));
        table->addPoint(xArray[i], y);
    }
    return table;
}
