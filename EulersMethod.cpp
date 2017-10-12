//
// Created by root on 10/13/17.
//

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "EulersMethod.h"

using namespace std;

// y' =
double F(double x, double y){
    return 3*sin(2*y)+x;
}

int EulersMethod::apply(double a, double b, double h) {
    //double a = 0;
   // double b = 1;
   // double h=0.1;
    double n=(b-a)/h;
    double X[(int)n]; double Y[(int)n];
    X[0]=a; Y[0]=2;
    for(int i=1; i<=n; i++){
        X[i]=a+i*h;
        Y[i]=Y[i-1]+h*F(X[i-1],Y[i-1]);
    }
    for(int i=0; i<=n; i++){
        cout << "X["<<i<<"]="<<X[i] <<" ";
    }
    cout << endl;
    for(int i=0; i<=n; i++){
        cout << "Y["<<i<<"]="<<Y[i] << " ";
    }
    return 0;
}
