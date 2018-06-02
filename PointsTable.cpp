//
// Created by alex on 16.10.17.
//

#include <iostream>
#include <sstream>
#include "PointsTable.h"

PointsTable::PointsTable() {
    points = new std::map<double, double>();
}

PointsTable::PointsTable(const string &ordinate) : ordinate(ordinate) {
    points = new std::map<double, double>();
}

PointsTable::PointsTable(map<double, double> *points) : points(points) {}

PointsTable::PointsTable(const string &coordName, map<double, double> *points) : ordinate(coordName), points(points) {}

void PointsTable::clear() {
    PointsTable::points->clear();
}

void PointsTable::addPoint(double x, double y) {
    points->insert(pair<double, double>(x, y));
}

void PointsTable::removePoint(double x) {
    points->erase(x);
}

double PointsTable::getY(double x) {
    return points->at(x);
}

double PointsTable::getX(double y) {
    for (auto &point : *points) {
        if (point.second == y) return point.first;
    }
    return NULL;
}

void PointsTable::replacePoint(double x, double y) {
    points->at(x) = y;
}

string PointsTable::stringifyPoint(pair<double, double> point) {
    stringstream result;
    result << string("{") << abscissa << string(":\'") << to_string(point.first)
           << string("\', ") << ordinate << string(":\'") << to_string(point.second) << "\'}";
    return result.str();
}

string PointsTable::toString() {
    stringstream result;
    result << string("PointsTable:[");
    bool first = true;
    for (auto &point : *points) {
        if (!first) result << "," << endl;
        result << stringifyPoint(point);
        first = false;
    }
    result << "]";
    return result.str();
}

string PointsTable::pointToJson(pair<double, double> point) {
    stringstream result;
    result << string("{\"") << abscissa << string("\":\"") << to_string(point.first)
           << string(R"(", ")") << ordinate << string(R"(":")") << to_string(point.second) << "\"}";
    return result.str();
}

string PointsTable::toJson() {
    stringstream result;
    result << string("[");
    bool first = true;
    for (auto &point : *points) {
        if (!first) result << "," << endl;
        result << pointToJson(point);
        first = false;
    }
    result << "]";
    return result.str();
}

map<double, double> *PointsTable::getPoints() const {
    return points;
}

void PointsTable::setPoints(map<double, double> *points) {
    PointsTable::points = points;
}

PointsTable::~PointsTable() {
    delete points;
}

const string &PointsTable::getAbscissa() const {
    return abscissa;
}

void PointsTable::setAbscissa(const string &abscissa) {
    PointsTable::abscissa = abscissa;
}

const string &PointsTable::getOrdinate() const {
    return ordinate;
}

void PointsTable::setOrdinate(const string &ordinate) {
    PointsTable::ordinate = ordinate;
}

PointsTable::PointsTable(const string &abscissa, const string &ordinate) : abscissa(abscissa), ordinate(ordinate) {}
