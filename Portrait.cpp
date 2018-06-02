//
// Created by alex on 02.06.18.
//

#include "Portrait.h"
#include <sstream>

Portrait::Portrait() {
    points = new list<pair<double, double>>();
}

const string &Portrait::getAbscissa() const {
    return abscissa;
}

void Portrait::setAbscissa(const string &abscissa) {
    Portrait::abscissa = abscissa;
}

const string &Portrait::getOrdinate() const {
    return ordinate;
}

void Portrait::setOrdinate(const string &ordinate) {
    Portrait::ordinate = ordinate;
}

list<pair<double, double>> *Portrait::getPoints() const {
    return points;
}

void Portrait::setPoints(list<pair<double, double>> *points) {
    Portrait::points = points;
}

Portrait::~Portrait() {
    delete(points);
}

void Portrait::clear() {
    points->clear();
}

void Portrait::addPoint(double x, double y) {
    pair<double, double> p = pair<double, double>(x, y);
    points->push_back(p);
}

string Portrait::pointToJson(pair<double, double> point) {
    stringstream result;
    result << string("{\"") << abscissa << string("\":\"") << to_string(point.first)
           << string(R"(", ")") << ordinate << string(R"(":")") << to_string(point.second) << "\"}";
    return result.str();
}

string Portrait::toJson() {
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
