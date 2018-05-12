#include <iostream>
#include <list>
#include "InitialData.h"
#include "EulersMethod.h"
#include "RungeKuttaMethod.h"
#include "ExportUtils.h"
#include "HeunsMethod.h"

using namespace std;

// TODO: move all the dynamically generated code somewhere else
int main() {
    // artificially generating initial data
    auto *initialData = new InitialData();
    initialData->setX0(0.01);
    initialData->setY0(0.01);
    initialData->setT0(0.01);
    initialData->setTFinal(1);
    double h = 0.02;

    Result *result = RungeKuttaMethod().apply(initialData, h);


//#pragma omp parallel for
//    for (int i = 0; i <= initialData->getIntervalsCount(); ++i) {
//        PointsTable *pointsTableX, *pointsTableY, *pointsTableZ;
//        Result *result = EulersMethod::apply(initialData, h);
//        pointsTableY = RungeKuttaMethod::apply(firstDerivativeY, initialData->getY0(), intervals[i].t0, intervals[i].tFinal, h);
//        pointsTableZ = HeunsMethod::apply(firstDerivativeZ, initialData->getZ0(), intervals[i].t0, intervals[i].tFinal, h);
//
//        delete pointsTableX;
//        delete pointsTableY;
//        delete pointsTableZ;
//    }

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
    cout << "X table" << endl;
    cout << result->getXTable()->toJson() << endl;
    cout << "Y table" << endl;
    cout << result->getYTable()->toJson() << endl;
    cout << "Z table" << endl;
    cout << result->getZTable()->toJson() << endl;
    cout << "XY phase portrait" << endl;
    cout << result->getXYPhasePortrait()->toJson() << endl;

    return 0;
}