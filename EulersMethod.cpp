//
// Created by root on 10/13/17.
//

#include <cstdlib>
#include "EulersMethod.h"

using namespace std;

static PointsTable *EulersMethod::apply(double (*firstDerivative)(double, double), double a, double b, double h) {
//static PointsTable *EulersMethod::apply(double &firstDerivative(double, double), double a, double b, double h) {
    double n = (b - a) / h;
    double xArray[(int) n];
    auto table = new PointsTable();

    // TODO: What is 2?
    table->addPoint(a, 2);
    //xArray[0] = a; yArray[0] = 2;
    for (int i = 1; i <= n; i++) {
        xArray[i] = a + i * h;
        double y = table->getY(xArray[i - 1]) + h * (*firstDerivative)(xArray[i - 1], table->getY(xArray[i - 1]));
        table->addPoint(xArray[i], y);
    }
    return table;
}
