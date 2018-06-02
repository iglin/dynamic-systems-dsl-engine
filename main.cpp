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
#include "DormandPrinceMethod.h"
#include "Portrait.h"

using namespace std;

const int ITERATIONS = 3;
const int ORDER = 100;

int main() {
    auto *initialData = new InitialData();
    initialData->setX0(0.8);
    initialData->setY0(0.5);
    //initialData->setZ0(0.011);
    initialData->setT0(0);
    initialData->setTFinal(3);
    double h = 0.001;

    Result *result = RungeKuttaMethod().apply(initialData, h);
    cout << result->getXYPhasePortrait()->toJson();

    ExportUtils::phasePortrait("xy.html", result->getXYPhasePortrait());

    Portrait *table = new Portrait();
    table->setAbscissa("x");
    table->setOrdinate("y");
    table->addPoint(-0.9, 5.1);
    table->addPoint(0, 4);
    table->addPoint(-1, 5);
    table->addPoint(-2, 3);
    table->addPoint(4, 8);
    cout << endl << table->toJson();
    ExportUtils::phasePortrait("wat.html", table);

    return 0;
}

// TODO: move all the dynamically generated code somewhere else
int main2() {
    // artificially generating initial data
    auto *initialData = new InitialData();
    initialData->setX0(0.011);
    initialData->setY0(0.011);
    initialData->setZ0(0.011);
    initialData->setT0(0);
    initialData->setTFinal(20);
    double h = 0.0002;

    double t1, t2;
    for (int i = 0; i < ITERATIONS; i++) {
        t1 = omp_get_wtime();
        Result *result = Extrapolation().applyRational(new DormandPrinceMethod(), initialData, h, ORDER);
        t2 = omp_get_wtime();
        cout << "Seq, " << t2 - t1 << endl;
    }
//    for (int i = 0; i < 5; i++) {
//        t1 = omp_get_wtime();
//        Result *result = Extrapolation().applyRationalOMP(new DormandPrinceMethod(), initialData, h, 8);
//        t2 = omp_get_wtime();
//        cout << "OMP, " << t2 - t1 << endl;
//    }
    cout << "Templet:" << endl;
    for (int i = 0; i < ITERATIONS; i++) {
        t1 = omp_get_wtime();
        Result *result = Extrapolation().applyRationalParallel(new DormandPrinceMethod(), initialData, h, ORDER);
        t2 = omp_get_wtime();
        cout << t2 - t1 << endl;
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

//    ExportUtils::graph("xy.html", result->getXYPhasePortrait());
//    result->getXTable()->setCoordName("y");
//    ExportUtils::graph("x.html", result->getXTable());
//    ExportUtils::graph("y.html", result->getYTable());

    return 0;
}