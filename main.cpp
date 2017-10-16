#include <iostream>
#include "InitialData.h"

using namespace std;

double func(double x) {
    return x*x;
}

double printer(double (*f)(double) ) {
    cout << (*f)(5);
}

int main() {
    cout << "Hello, World!" << endl;
    //printer(func);

    auto *initialData = new InitialData();
    cout << initialData->firstDerivativeX(3, 5);
    return 0;
}