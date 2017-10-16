#include <iostream>
#include "InitialData.h"
#include "EulersMethod.h"

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

    EulersMethod::apply(initialData->firstDerivativeX,
                                           initialData->getT0(),
                                           initialData->getTFinal(),
                                           h
    );
    // << pointsTable->toString() << endl;

    return 0;
}