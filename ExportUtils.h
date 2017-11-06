//
// Created by root on 10/29/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_EXPORTUTILS_H
#define DYNAMIC_SYSTEMS_DSL_EXPORTUTILS_H

#include <iostream>
#include <list>
#include "PointsTable.h"

using namespace std;

class ExportUtils {
public:
    static void exportToCSV(list<PointsTable*> results, string fileName);

    static void graph(string fileName, PointsTable* pointsTable);
};


#endif //DYNAMIC_SYSTEMS_DSL_EXPORTUTILS_H
