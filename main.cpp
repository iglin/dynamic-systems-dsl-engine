#include <iostream>
#include "InitialData.h"
#include "EulersMethod.h"
#include "FirstDerivativeX.h"
#include "FirstDerivativeZ.h"
#include "FirstDerivativeY.h"
#include "RungeKuttaMethod.h"

using namespace std;

int main() {
    auto *initialData = new InitialData();
    initialData->setX0(2);
    initialData->setY0(2);
    initialData->setZ0(2);
    initialData->setT0(0);
    initialData->setTFinal(1);
    double h = 0.1;

    auto firstDerivativeX = new FirstDerivativeX();
    auto firstDerivativeY = new FirstDerivativeY();
    auto firstDerivativeZ = new FirstDerivativeZ();

    PointsTable *pointsTableX, *pointsTableY, *pointsTableZ;
#pragma omp parallel
    {
        pointsTableX = EulersMethod::apply(firstDerivativeX, initialData->getX0(), initialData->getT0(),
                                                initialData->getTFinal(), h);
        pointsTableY = EulersMethod::apply(firstDerivativeY, initialData->getY0(), initialData->getT0(),
                                                initialData->getTFinal(), h);
        pointsTableZ = RungeKuttaMethod::apply(firstDerivativeZ, initialData->getZ0(), initialData->getT0(),
                                                initialData->getTFinal(), h);
    }
    /*EulersMethod::apply(initialData->firstDerivativeX,
                                           initialData->getT0(),
                                           initialData->getTFinal(),
                                           h
    );*/
    cout << "X table" << endl;
    cout << pointsTableX->toString() << endl;
    cout << "Y table" << endl;
    cout << pointsTableY->toJson() << endl;
    cout << "Z table" << endl;
    cout << pointsTableZ->toJson() << endl;

    return 0;
}