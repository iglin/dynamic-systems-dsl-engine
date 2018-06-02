//
// Created by alex on 02.06.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_PORTRAIT_H
#define DYNAMIC_SYSTEMS_DSL_PORTRAIT_H

#include <list>
#include <string>
#include "ChartPoints.h"

using namespace std;

class Portrait : public ChartPoints {
private:
    string abscissa = string("x");
    string ordinate = string("y");
    list<pair<double, double>> *points;

    string stringifyPoint(pair<double, double> point);
    string pointToJson(pair<double, double> point);

public:
    Portrait();

    const string &getAbscissa() const;

    void setAbscissa(const string &abscissa);

    const string &getOrdinate() const;

    void setOrdinate(const string &ordinate);

    list<pair<double, double>> *getPoints() const;

    void setPoints(list<pair<double, double>> *points);

    virtual ~Portrait();

    void clear();

    void addPoint(double x, double y);

    void removePoint(double x);

    double getY(double x);

    double getX(double y);

    void replacePoint(double x, double y);

    string toString();

    string toJson() override;
};


#endif //DYNAMIC_SYSTEMS_DSL_PORTRAIT_H
