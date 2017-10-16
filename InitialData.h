//
// Created by root on 10/16/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_INITIALDATA_H
#define DYNAMIC_SYSTEMS_DSL_INITIALDATA_H


class InitialData {
private:
    double x0, y0, z0, t0, tFinal;
public:
    InitialData();

    InitialData(double x0, double y0, double z0, double t0, double tFinal);

    double firstDerivativeX(double x, double t);

    double firstDerivativeY(double y, double t);

    double firstDerivativeZ(double z, double t);

    double getY0() const;

    void setY0(double y0);

    double getZ0() const;

    void setZ0(double z0);

    double getT0() const;

    void setT0(double t0);

    double getTFinal() const;

    void setTFinal(double T);

    double getX0() const;

    void setX0(double x0);
};


#endif //DYNAMIC_SYSTEMS_DSL_INITIALDATA_H
