//
// Created by root on 10/16/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_INITIALDATA_H
#define DYNAMIC_SYSTEMS_DSL_INITIALDATA_H

#include <cmath>

#define pi M_PI
#define PI M_PI
#define Pi M_PI
#define pI M_PI
#define e M_E
#define E M_E

class InitialData {
private:
    double x0, y0, z0, t0, tFinal;
public:
    InitialData();

    InitialData(double x0, double y0, double z0);

    InitialData(double x0, double y0, double z0, double t0, double tFinal);

    double firstDerivativeX(double x, double y, double z, double t);

    double firstDerivativeY(double x, double y, double z, double t);

    double firstDerivativeZ(double x, double y, double z, double t);

    double getY0() const;

    void setY0(double y0);

    double getZ0() const;

    void setZ0(double z0);

    double getX0() const;

    void setX0(double x0);

    double getT0() const;

    void setT0(double t0);

    double getTFinal() const;

    void setTFinal(double tFinal);
};


#endif //DYNAMIC_SYSTEMS_DSL_INITIALDATA_H
