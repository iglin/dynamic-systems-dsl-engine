//
// Created by alex on 11.05.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_RESULT_H
#define DYNAMIC_SYSTEMS_DSL_RESULT_H


#include "PointsTable.h"

class Result {
private:
    PointsTable *xTable;
    PointsTable *yTable;
    PointsTable *zTable;

public:
    Result();

    Result(PointsTable *xTable, PointsTable *yTable, PointsTable *zTable);

    PointsTable *getXTable() const;

    void setXTable(PointsTable *xTable);

    PointsTable *getYTable() const;

    void setYTable(PointsTable *yTable);

    PointsTable *getZTable() const;

    void setZTable(PointsTable *zTable);
};


#endif //DYNAMIC_SYSTEMS_DSL_RESULT_H
