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

    PointsTable *xyPhasePortrait = nullptr;
    PointsTable *xzPhasePortrait = nullptr;
    PointsTable *yzPhasePortrait = nullptr;
public:
    Result();

    Result(PointsTable *xTable, PointsTable *yTable, PointsTable *zTable);

    PointsTable *getXTable() const;

    void setXTable(PointsTable *xTable);

    PointsTable *getYTable() const;

    void setYTable(PointsTable *yTable);

    PointsTable *getZTable() const;

    void setZTable(PointsTable *zTable);

    PointsTable *getXYPhasePortrait();

    PointsTable *getXZPhasePortrait();

    PointsTable *getYZPhasePortrait();
};


#endif //DYNAMIC_SYSTEMS_DSL_RESULT_H
