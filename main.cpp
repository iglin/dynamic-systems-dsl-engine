#include <iostream>
#include "InitialData.h"
#include "EulersMethod.h"
#include "FirstDerivativeX.h"

using namespace std;

double func(double x) {
    return x*x;
}

double printer(double (*f)(double) ) {
    cout << (*f)(5);
}

int main() {
    //printer(func);

    auto *initialData = new InitialData();
    initialData->setT0(0);
    initialData->setTFinal(1);
    double h = 0.1;

    auto firstDerivativeX = new FirstDerivativeX();
    cout << "first derivative x created" << endl;
    auto pointsTable = EulersMethod::apply(firstDerivativeX, initialData->getT0(), initialData->getTFinal(), h);
    /*EulersMethod::apply(initialData->firstDerivativeX,
                                           initialData->getT0(),
                                           initialData->getTFinal(),
                                           h
    );*/
    cout << "euler finished" << endl;
    cout << pointsTable->toString() << endl;

    return 0;
}