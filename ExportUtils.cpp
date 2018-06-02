//
// Created by root on 10/29/17.
//

#include <fstream>
#include <stdexcept>
#include "ExportUtils.h"

void ExportUtils::exportToCSV(list<PointsTable*> results, string fileName) {
    ofstream file(fileName);
    if (file.is_open()) {
        for (auto &result : results) {
            file << result->getOrdinate() << "(t)" << endl;
            file << "t, " << result->getOrdinate() << endl;
            for (auto &point : *result->getPoints()) {
                file << point.first << ", " << point.second << endl;
            }
            file << "," << endl;
        }
        file.close();
    } else {
        string errorMessage;
        errorMessage = "Could not write CSV report to file" + fileName;
        throw runtime_error(errorMessage);
    }
}

void ExportUtils::graph(const string &fileName, ChartPoints *pointsTable) {
    saveChart(GRAPH_PAGE_HEADER, GRAPH_PAGE_FOOTER, fileName, pointsTable);
}

void ExportUtils::phasePortrait(const string &fileName, ChartPoints *pointsTable) {
    saveChart(PHASE_PAGE_HEADER, PHASE_PAGE_FOOTER, fileName, pointsTable);
}

void ExportUtils::saveChart(const string &headerFilename, const string &footerFilename, const string &fileName, ChartPoints *pointsTable) {
    ofstream file(fileName);
    if (file.is_open()) {
        string *buffer = new string();
        ifstream headerFile(headerFilename);
        if (!headerFile.is_open()) throw runtime_error("Could not make chart");
        while(std::getline(headerFile, *buffer)) {
            file << *buffer << endl;
        }
        headerFile.close();

        file << pointsTable->toJson() << endl;

        ifstream footerFile(footerFilename);
        if (!footerFile.is_open()) throw runtime_error("Could not make chart");
        while(std::getline(footerFile, *buffer)) {
            file << *buffer << endl;
        }
        footerFile.close();
        delete buffer;
        file.close();
    } else {
        string errorMessage;
        errorMessage = "Could not write chart to file" + fileName;
        throw runtime_error(errorMessage);
    }
}
