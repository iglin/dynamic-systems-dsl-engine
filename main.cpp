#include <iostream>

using namespace std;

double func(double x) {
    return x*x;
}

double printer(double (*f)(double) ) {
    cout << (*f)(5);
}

int main() {
    cout << "Hello, World!" << endl;
    printer(func);
    return 0;
}