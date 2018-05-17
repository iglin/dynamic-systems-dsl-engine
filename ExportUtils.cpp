//
// Created by root on 10/29/17.
//

#include <fstream>
#include <stdexcept>
#include "ExportUtils.h"

//void ExportUtils::exportToCSV(list<PointsTable*> results, string fileName) {
//    ofstream file(fileName);
//    if (file.is_open()) {
//        for (auto &result : results) {
//            file << result->getCoordName() << "(t)" << endl;
//            file << "t, " << result->getCoordName() << endl;
//            for (auto &point : *result->getPoints()) {
//                file << point.first << ", " << point.second << endl;
//            }
//            file << "," << endl;
//        }
//        file.close();
//    } else {
//        string errorMessage;
//        errorMessage = "Could not write CSV report to file" + fileName;
//        throw runtime_error(errorMessage);
//    }
//}
//
//void ExportUtils::graph(string fileName, PointsTable *pointsTable) {
//    ofstream file(fileName);
//    if (file.is_open()) {
//        string *buffer = new string();
//        ifstream headerFile(CHART_PAGE_HEADER);
//        if (!headerFile.is_open()) throw runtime_error("Could not make chart");
//        while(std::getline(headerFile, *buffer)) {
//            file << *buffer << endl;
//        }
//        headerFile.close();
//
//        file << pointsTable->toJson() << endl;
//
//        ifstream footerFile(CHART_PAGE_FOOTER);
//        if (!footerFile.is_open()) throw runtime_error("Could not make chart");
//        while(std::getline(footerFile, *buffer)) {
//            file << *buffer << endl;
//        }
//        footerFile.close();
//        delete buffer;
//        file.close();
//    } else {
//        string errorMessage;
//        errorMessage = "Could not write chart to file" + fileName;
//        throw runtime_error(errorMessage);
//    }
//}
