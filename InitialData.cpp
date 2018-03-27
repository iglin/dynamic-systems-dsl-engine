//
// Created by root on 10/16/17.
//

#include "InitialData.h"
#include <cmath>
#include <stdexcept>

#define dx (3 * sin(2 * x) + t)
#define dy (4 * cos(2 * y) + pow(t, 7))
#define dz (-3 * sin(2 * z) * sqrt(t))


InitialData::InitialData() = default;

InitialData::InitialData(double x0, double y0, double z0) : x0(x0), y0(y0), z0(z0) {}

InitialData::InitialData(double x0, double y0, double z0, InitialData::Interval *intervals, int intervalsCount) : x0(
        x0), y0(y0), z0(z0), intervals(intervals), intervalsCount(intervalsCount) {}

double InitialData::firstDerivativeX(double x, double t) {
#if defined(dx)
    return dx;
#else
    throw std::invalid_argument( "dx/dt is not defined!" );
#endif
}

double InitialData::firstDerivativeY(double y, double t) {
#if defined(dy)
    return dy;
#else
    throw std::invalid_argument( "dy/dt is not defined!" );
#endif
}

double InitialData::firstDerivativeZ(double z, double t) {
#if defined(dz)
    return dz;
#else
    throw std::invalid_argument( "dz/dt is not defined!" );
#endif
}

double InitialData::getX0() const {
    return x0;
}

void InitialData::setX0(double x0) {
    InitialData::x0 = x0;
}

double InitialData::getY0() const {
    return y0;
}

void InitialData::setY0(double y0) {
    InitialData::y0 = y0;
}

double InitialData::getZ0() const {
    return z0;
}

void InitialData::setZ0(double z0) {
    InitialData::z0 = z0;
}

InitialData::Interval *InitialData::getIntervals() const {
    return intervals;
}

void InitialData::setIntervals(InitialData::Interval *intervals) {
    InitialData::intervals = intervals;
}

int InitialData::getIntervalsCount() const {
    return intervalsCount;
}

void InitialData::setIntervalsCount(int intervalsCount) {
    InitialData::intervalsCount = intervalsCount;
}

InitialData::Interval::Interval(double t0, double tFinal) : t0(t0), tFinal(tFinal) {}

InitialData::Interval::Interval() {}
