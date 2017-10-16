//
// Created by root on 10/13/17.
//

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "EulersMethod.h"

using namespace std;

int EulersMethod::apply(double (*firstDerivative)(double, double), double a, double b, double h) {
    //double a = 0;
   // double b = 1;
   // double h=0.1;
    double n = (b - a) / h;
    double xArray[(int) n]; double yArray[(int) n];
    xArray[0]=a; yArray[0]=2;
    for(int i = 1; i <= n; i++){
        xArray[i]=a + i * h;
        yArray[i]=yArray[i-1]+h * (*firstDerivative)(xArray[i - 1], yArray[i - 1]);
    }
    for(int i=0; i<=n; i++){
        cout << "X["<<i<<"]="<<xArray[i] <<" ";
    }
    cout << endl;
    for(int i=0; i<=n; i++){
        cout << "Y["<<i<<"]="<<yArray[i] << " ";
    }
    return EXIT_SUCCESS;
}
