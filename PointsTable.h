//
// Created by alex on 16.10.17.
//

#ifndef DYNAMIC_SYSTEMS_DSL_POINTSTABLE_H
#define DYNAMIC_SYSTEMS_DSL_POINTSTABLE_H

#include <map>
#include <string>

using namespace std;

class PointsTable {
private:
    string coordName = string("x");
    map<double, double> *points;

    string stringifyPoint(pair<double, double> point);
    string pointToJson(pair<double, double> point);
public:
    PointsTable();

    PointsTable(map<double, double> *points);

    explicit PointsTable(const string &coordName);

    PointsTable(const string &coordName, map<double, double> *points);

    virtual ~PointsTable();

    void clear();

    void addPoint(double x, double y);

    void removePoint(double x);

    double getY(double x);

    double getX(double y);

    void replacePoint(double x, double y);

    const string &getCoordName() const;

    void setCoordName(const string &coordName);

    map<double, double> *getPoints() const;

    void setPoints(map<double, double> *points);

    string toString();

    string toJson();
};


#endif //DYNAMIC_SYSTEMS_DSL_POINTSTABLE_H
