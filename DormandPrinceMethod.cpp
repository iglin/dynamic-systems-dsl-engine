//
// Created by alex on 16.05.18.
//

#include "DormandPrinceMethod.h"


Result *DormandPrinceMethod::apply(InitialData *data, double h) {
    int n = static_cast<int>(round((data->getTFinal() - data->getT0()) / h));
    double tArray[n];
    PointsTable *xTable = new PointsTable("x");
    PointsTable *yTable = new PointsTable("y");
    PointsTable *zTable = new PointsTable("z");
#if defined(dx)
    xTable->addPoint(data->getT0(), data->getX0());
#endif
#if defined(dy)
    yTable->addPoint(data->getT0(), data->getY0());
#endif
#if defined(dz)
    zTable->addPoint(data->getT0(), data->getZ0());
#endif
    tArray[0] = data->getT0();
    for (int i = 1; i < n; i++) {
        tArray[i] = tArray[i - 1] + h;

#if defined(dx)
#if defined(dy)
#if defined(dz)
        xTable->addPoint(tArray[i], calculateNextX(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]), tArray[i - 1], h));
        yTable->addPoint(tArray[i], calculateNextY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]), tArray[i - 1], h));
        zTable->addPoint(tArray[i], calculateNextZ(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), zTable->getY(tArray[i - 1]), tArray[i - 1], h));
#else
        xTable->addPoint(tArray[i], calculateNextX(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), 0, tArray[i - 1], h));
        yTable->addPoint(tArray[i], calculateNextY(xTable->getY(tArray[i - 1]), yTable->getY(tArray[i - 1]), 0, tArray[i - 1], h));
#endif
#else
        xTable->addPoint(tArray[i], calculateNextX(xTable->getY(tArray[i - 1]), 0, 0, tArray[i - 1], h));
#endif
#endif
    }
    return new Result(xTable, yTable, zTable);
}


//TODO: return with error estimate
double DormandPrinceMethod::calculateNextX(double xPrev, double yPrev, double zPrev, double tPrev, double h) {
    double k1 = InitialData::derivativeX(xPrev, yPrev, zPrev, tPrev);
    double k2 = InitialData::derivativeX(xPrev + h * (k1 / 5), yPrev, zPrev, tPrev + h / 5);
    double k3 = InitialData::derivativeX(xPrev + h * ((3.0 / 40) * k1 + (9.0 / 40) * k2), yPrev, zPrev, tPrev + h * 0.3);
    double k4 = InitialData::derivativeX(xPrev + h * ((44.0 / 45) * k1 + (-56.0 / 15) * k2 + (32.0 / 9) * k3), yPrev, zPrev, tPrev + h * 4 / 5);
    double k5 = InitialData::derivativeX(xPrev + h * ((19372.0 / 6561) * k1 + (-25360.0 / 2187) * k2
            + (64448.0 / 6561) * k3 + (-212.0 / 729) * k4), yPrev, zPrev, tPrev + h * 8 / 9);
    double k6 = InitialData::derivativeX(xPrev + h * ((9017.0 / 3168) * k1 + (-355.0 / 33) * k2
            + (46732.0 / 5247) * k3 + (49.0 / 176) * k4 + (-5103.0 / 18656) * k5), yPrev, zPrev, tPrev + h);
    double k7 = InitialData::derivativeX(xPrev + h * ((35.0 / 384) * k1 + (500.0 / 1113) * k3
            + (125.0 / 192) * k4 + (-2187.0 / 6784) * k5 + (11.0 / 84) * k5), yPrev, zPrev, tPrev + h);
    double v1 = xPrev + h * ((35.0 / 384) * k1 + (500.0 / 1113) * k3 + (125.0 / 192) * k4 + (-2187.0 / 6784) * k5 + (11.0/84) * k6);
    double v2 = xPrev + h * ((5179.0 / 57600) * k1 + (7571.0 / 16695) * k3 + (393.0 / 640) * k4 + (-92097.0 / 339200) * k5
            + (187.0 / 2100) * k6 + (1.0 / 40) * k6);
    double error = v1 - v2;
    return v1;
}

double DormandPrinceMethod::calculateNextY(double xPrev, double yPrev, double zPrev, double tPrev, double h) {
    double k1 = InitialData::derivativeX(xPrev, yPrev, zPrev, tPrev);
    double k2 = InitialData::derivativeX(xPrev, yPrev + h * (k1 / 5), zPrev, tPrev + h / 5);
    double k3 = InitialData::derivativeX(xPrev, yPrev + h * ((3.0 / 40) * k1 + (9.0 / 40) * k2), zPrev, tPrev + h * 0.3);
    double k4 = InitialData::derivativeX(xPrev, yPrev + h * ((44.0 / 45) * k1 + (-56.0 / 15) * k2 + (32.0 / 9) * k3), zPrev, tPrev + h * 4 / 5);
    double k5 = InitialData::derivativeX(xPrev, yPrev + h * ((19372.0 / 6561) * k1 + (-25360.0 / 2187) * k2
            + (64448.0 / 6561) * k3 + (-212.0 / 729) * k4), zPrev, tPrev + h * 8 / 9);
    double k6 = InitialData::derivativeX(xPrev, yPrev + h * ((9017.0 / 3168) * k1 + (-355.0 / 33) * k2
            + (46732.0 / 5247) * k3 + (49.0 / 176) * k4 + (-5103.0 / 18656) * k5), zPrev, tPrev + h);
    double k7 = InitialData::derivativeX(xPrev, yPrev + h * ((35.0 / 384) * k1 + (500.0 / 1113) * k3
            + (125.0 / 192) * k4 + (-2187.0 / 6784) * k5 + (11.0 / 84) * k5), zPrev, tPrev + h);
    double v1 = xPrev + h * ((35.0 / 384) * k1 + (500.0 / 1113) * k3 + (125.0 / 192) * k4 + (-2187.0 / 6784) * k5 + (11.0/84) * k6);
    double v2 = xPrev + h * ((5179.0 / 57600) * k1 + (7571.0 / 16695) * k3 + (393.0 / 640) * k4 + (-92097.0 / 339200) * k5
                             + (187.0 / 2100) * k6 + (1.0 / 40) * k6);
    double error = v1 - v2;
    return v1;
}

double DormandPrinceMethod::calculateNextZ(double xPrev, double yPrev, double zPrev, double tPrev, double h) {
    double k1 = InitialData::derivativeX(xPrev, yPrev, zPrev, tPrev);
    double k2 = InitialData::derivativeX(xPrev, yPrev, zPrev + h * (k1 / 5), tPrev + h / 5);
    double k3 = InitialData::derivativeX(xPrev, yPrev, zPrev + h * ((3.0 / 40) * k1 + (9.0 / 40) * k2), tPrev + h * 0.3);
    double k4 = InitialData::derivativeX(xPrev, yPrev, zPrev + h * ((44.0 / 45) * k1 + (-56.0 / 15) * k2 + (32.0 / 9) * k3), tPrev + h * 4 / 5);
    double k5 = InitialData::derivativeX(xPrev, yPrev, zPrev + h * ((19372.0 / 6561) * k1 + (-25360.0 / 2187) * k2
            + (64448.0 / 6561) * k3 + (-212.0 / 729) * k4), tPrev + h * 8 / 9);
    double k6 = InitialData::derivativeX(xPrev, yPrev, zPrev + h * ((9017.0 / 3168) * k1 + (-355.0 / 33) * k2
            + (46732.0 / 5247) * k3 + (49.0 / 176) * k4 + (-5103.0 / 18656) * k5), tPrev + h);
    double k7 = InitialData::derivativeX(xPrev, yPrev, zPrev + h * ((35.0 / 384) * k1 + (500.0 / 1113) * k3
            + (125.0 / 192) * k4 + (-2187.0 / 6784) * k5 + (11.0 / 84) * k5), tPrev + h);
    double v1 = xPrev + h * ((35.0 / 384) * k1 + (500.0 / 1113) * k3 + (125.0 / 192) * k4 + (-2187.0 / 6784) * k5 + (11.0/84) * k6);
    double v2 = xPrev + h * ((5179.0 / 57600) * k1 + (7571.0 / 16695) * k3 + (393.0 / 640) * k4 + (-92097.0 / 339200) * k5
                             + (187.0 / 2100) * k6 + (1.0 / 40) * k6);
    double error = v1 - v2;
    return v1;
}
