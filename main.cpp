#include <iostream>
#include <list>
#include "InitialData.h"
#include "EulersMethod.h"
#include "FirstDerivativeX.h"
#include "FirstDerivativeZ.h"
#include "FirstDerivativeY.h"
#include "RungeKuttaMethod.h"
#include "ExportUtils.h"

using namespace std;

// TODO: move all the dynamically generated code somewhere else
int main() {
    InitialData::Interval intervals[2];
    intervals[0] = InitialData::Interval(0, 1);
    intervals[1] = InitialData::Interval(2, 4);
    auto *initialData = new InitialData();
    initialData->setX0(2);
    initialData->setY0(2);
    initialData->setZ0(2);
    initialData->setIntervals(intervals);
    initialData->setIntervalsCount(2);
    double h = 0.1;

    auto firstDerivativeX = new FirstDerivativeX(initialData);
    auto firstDerivativeY = new FirstDerivativeY(initialData);
    auto firstDerivativeZ = new FirstDerivativeZ(initialData);

    PointsTable *pointsTableX, *pointsTableY, *pointsTableZ;
#pragma omp parallel for
    for (int i = 0; i <= initialData->getIntervalsCount(); ++i) {
        pointsTableX = EulersMethod::apply(firstDerivativeX, initialData->getX0(), intervals[i].t0, intervals[i].tFinal, h);
        pointsTableY = EulersMethod::apply(firstDerivativeY, initialData->getY0(), intervals[i].t0, intervals[i].tFinal, h);
        pointsTableZ = RungeKuttaMethod::apply(firstDerivativeZ, initialData->getZ0(), intervals[i].t0, intervals[i].tFinal, h);

        // save results somehow

        delete [] pointsTableX;
        delete pointsTableY;
        delete [] pointsTableZ;
    }
    pointsTableX->setCoordName("x");
    pointsTableY->setCoordName("y");
    pointsTableZ->setCoordName("z");
    /*EulersMethod::apply(initialData->firstDerivativeX,
                                           initialData->getT0(),
                                           initialData->getTFinal(),
                                           h
    );*/

    list<PointsTable*> result;
    result.push_back(pointsTableX);
    result.push_back(pointsTableY);
    result.push_back(pointsTableZ);
    ExportUtils::exportToCSV(result, "out.csv");

    cout << "X table" << endl;
    cout << pointsTableX->toString() << endl;
    cout << "Y table" << endl;
    cout << pointsTableY->toJson() << endl;
    cout << "Z table" << endl;
    cout << pointsTableZ->toJson() << endl;

    return 0;
}