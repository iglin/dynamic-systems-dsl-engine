//
// Created by root on 10/29/17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_EXPORTUTILS_H
#define DYNAMIC_SYSTEMS_DSL_EXPORTUTILS_H

#include <iostream>
#include <list>
#include "PointsTable.h"
#include "ChartPoints.h"

using namespace std;

static const string GRAPH_PAGE_HEADER = "../resources/amcharts.header.html";
static const string GRAPH_PAGE_FOOTER = "../resources/amcharts.footer.html";
static const string PHASE_PAGE_HEADER = "../resources/phase.header.html";
static const string PHASE_PAGE_FOOTER = "../resources/phase.footer.html";

class ExportUtils {
public:
    static void exportToCSV(list<PointsTable*> results, string fileName);

    static void graph(const string &fileName, ChartPoints* pointsTable);

    static void phasePortrait(const string &fileName, ChartPoints* pointsTable);
private:
    static void saveChart(const string &headerFilename, const string &footerFilename, const string &fileName, ChartPoints* pointsTable);
};


#endif //DYNAMIC_SYSTEMS_DSL_EXPORTUTILS_H
