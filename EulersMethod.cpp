//
// Created by root on 10/13/17.
//

#include <cstdlib>
#include <iostream>
#include "EulersMethod.h"
#include "FirstDerivative.h"

using namespace std;

/* Through method ref, doesn't work
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
}*/

PointsTable *EulersMethod::apply(FirstDerivative *firstDerivative, double a, double b, double h) {
    cout << "method started" << endl;
    double n = (b - a) / h;
    double xArray[(int) n];
    auto table = new PointsTable();

    cout << "table created" << endl;
    // TODO: What is 2?
    table->addPoint(a, 2);
    //printf("table %d is %lf", 0, table->getY(0));
    xArray[0] = a; //yArray[0] = 2;
    for (int i = 1; i <= n; i++) {
        cout << "iteration started: " << i << endl;
        xArray[i] = a + i * h;
        double y = table->getY(xArray[i - 1]) + h * firstDerivative->calculate(xArray[i - 1], table->getY(xArray[i - 1]));
        table->addPoint(xArray[i], y);
    }
    return table;
}
