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
            file << result->getCoordName() << "(t)" << endl;
            file << "t, " << result->getCoordName() << endl;
            for (auto &point : result->getPoints()) {
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

void ExportUtils::graph(string fileName, PointsTable *pointsTable) {
    cout << "This is stub for graph export of solution: " << endl;
    cout << pointsTable->toJson() << endl;
}
