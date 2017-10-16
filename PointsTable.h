//
// Created by alex on 16.10.17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_POINTSTABLE_H
#define DYNAMIC_SYSTEMS_DSL_POINTSTABLE_H

#include <map>

using namespace std;

class PointsTable {
private:
    map<double, double> points;

    string stringifyPoint(pair<double, double> point);
public:
    PointsTable();

    explicit PointsTable(map<double, double> points);

    void clear();

    void addPoint(double x, double y);

    void removePoint(double x);

    double getY(double x);

    double getX(double y);

    void replacePoint(double x, double y);

    const map<double, double> &getPoints() const;

    void setPoints(const map<double, double> &points);

    string toString();
};


#endif //DYNAMIC_SYSTEMS_DSL_POINTSTABLE_H
