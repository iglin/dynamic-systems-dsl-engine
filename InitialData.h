//
// Created by root on 10/16/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_INITIALDATA_H
#define DYNAMIC_SYSTEMS_DSL_INITIALDATA_H


class InitialData {
public:
    struct Interval {
        double t0 = 0;
        double tFinal = 1;

        Interval();

        Interval(double t0, double tFinal);
    };
private:
    double x0, y0, z0;
    Interval *intervals;
    int intervalsCount;
public:
    InitialData();

    InitialData(double x0, double y0, double z0);

    InitialData(double x0, double y0, double z0, Interval *intervals, int intervalsCount);

    double firstDerivativeX(double x, double t);

    double firstDerivativeY(double y, double t);

    double firstDerivativeZ(double z, double t);

    double getY0() const;

    void setY0(double y0);

    double getZ0() const;

    void setZ0(double z0);

    double getX0() const;

    void setX0(double x0);

    Interval *getIntervals() const;

    void setIntervals(Interval *intervals);

    int getIntervalsCount() const;

    void setIntervalsCount(int intervalsCount);
};


#endif //DYNAMIC_SYSTEMS_DSL_INITIALDATA_H
