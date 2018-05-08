#include <iostream>
#include <list>
#include "InitialData.h"
#include "EulersMethod.h"
#include "FirstDerivativeX.h"
#include "FirstDerivativeZ.h"
#include "FirstDerivativeY.h"
#include "RungeKuttaMethod.h"
#include "ExportUtils.h"
#include "HeunsMethod.h"

using namespace std;

// TODO: move all the dynamically generated code somewhere else
int main() {
    // artificially generating initial data
    auto *initialData = new InitialData();
    initialData->setX0(2);
    initialData->setY0(2);
    initialData->setZ0(2);
    const int intervalsCount = 500000;
    initialData->setIntervalsCount(intervalsCount);
    InitialData::Interval intervals[intervalsCount];
    for (int i = 0; i < intervalsCount; i++) {
        intervals[i] = InitialData::Interval(i, i + 7);
    }
    initialData->setIntervals(intervals);
    double h = 0.1;

    auto firstDerivativeX = new FirstDerivativeX(initialData);
    auto firstDerivativeY = new FirstDerivativeY(initialData);
    auto firstDerivativeZ = new FirstDerivativeZ(initialData);

#pragma omp parallel for
    for (int i = 0; i <= initialData->getIntervalsCount(); ++i) {
        PointsTable *pointsTableX, *pointsTableY, *pointsTableZ;
        pointsTableX = EulersMethod::apply(firstDerivativeX, initialData->getX0(), intervals[i].t0, intervals[i].tFinal, h);
        pointsTableY = RungeKuttaMethod::apply(firstDerivativeY, initialData->getY0(), intervals[i].t0, intervals[i].tFinal, h);
        pointsTableZ = HeunsMethod::apply(firstDerivativeZ, initialData->getZ0(), intervals[i].t0, intervals[i].tFinal, h);

        delete pointsTableX;
        delete pointsTableY;
        delete pointsTableZ;
    }

//    Export utils sample usage
//    pointsTableX->setCoordName("x");
//    pointsTableY->setCoordName("y");
//    pointsTableZ->setCoordName("z");
//
//    list<PointsTable*> result;
//    result.push_back(pointsTableX);
//    result.push_back(pointsTableY);
//    result.push_back(pointsTableZ);
//    ExportUtils::exportToCSV(result, "out.csv");
//
//    cout << "X table" << endl;
//    cout << pointsTableX->toString() << endl;
//    cout << "Y table" << endl;
//    cout << pointsTableY->toString() << endl;
//    cout << "Z table" << endl;
//    cout << pointsTableZ->toString() << endl;
//    cout << pointsTableZ->toJson() << endl;

    return 0;
}