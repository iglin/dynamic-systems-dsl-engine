//
// Created by alex on 16.10.17.
//

#include <iostream>
#include <sstream>
#include "PointsTable.h"

PointsTable::PointsTable() = default;

PointsTable::PointsTable(map<double, double> points) : points(std::move(points)) {}

const map<double, double> &PointsTable::getPoints() const {
    return points;
}

void PointsTable::setPoints(const map<double, double> &points) {
    PointsTable::points = points;
}

void PointsTable::clear() {
    PointsTable::points.clear();
}

void PointsTable::addPoint(double x, double y) {
    points.insert(pair<double, double>(x, y));
}

void PointsTable::removePoint(double x) {
    points.erase(x);
}

double PointsTable::getY(double x) {
    return points.at(x);
}

double PointsTable::getX(double y) {
    for (auto it = points.begin(); it != points.end();) {
        if (it->second == y) return it->first;
    }
    return NULL;
}

void PointsTable::replacePoint(double x, double y) {
    points.at(x) = y;
}

string PointsTable::stringifyPoint(pair<double, double> point) {
    stringstream result;
    result << string("{x:\'") << to_string(point.first)
           << string("\', y:\'") << to_string(point.second) << "\'}";
    return result.str();
}

string PointsTable::toString() {
    stringstream result;
    result << string("PointsTable:[");
    for (auto it = points.begin(); it != points.end();) {
        result << stringifyPoint(*it);
        if (it != points.end()) result << "," << endl;
    }
    result << "]";
    return result.str();
}


