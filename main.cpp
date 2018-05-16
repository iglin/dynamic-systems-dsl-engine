#include <iostream>
#include <list>
#include <omp.h>
#include "InitialData.h"
#include "EulersMethod.h"
#include "RungeKuttaMethod.h"
#include "ExportUtils.h"
#include "HeunsMethod.h"
#include "SimpsonsMethod.h"
#include "Extrapolation.h"

using namespace std;

// TODO: move all the dynamically generated code somewhere else
int main() {
    // artificially generating initial data
    auto *initialData = new InitialData();
    initialData->setX0(0.011);
    initialData->setY0(0.011);
    initialData->setT0(0);
    initialData->setTFinal(100);
    double h = 0.0002;

    double t1 = omp_get_wtime(), t2;
    Result *result = Extrapolation().applyRational(initialData, h, 8);
    t2 = omp_get_wtime();
    cout << t2 - t1 << endl;
    t1 = omp_get_wtime();
    result = Extrapolation().applyRationalParallel(new EulersMethod(), initialData, h);
    t2 = omp_get_wtime();
    cout << t2 - t1 << endl;


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

//    ExportUtils::graph("xy.html", result->getXYPhasePortrait());
//    result->getXTable()->setCoordName("y");
//    ExportUtils::graph("x.html", result->getXTable());
//    ExportUtils::graph("y.html", result->getYTable());

    return 0;
}