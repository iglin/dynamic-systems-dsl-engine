//
// Created by alex on 11.05.18.
//

#include "Result.h"

PointsTable *Result::getXTable() const {
    return xTable;
}

void Result::setXTable(PointsTable *xTable) {
    Result::xTable = xTable;
}

PointsTable *Result::getYTable() const {
    return yTable;
}

void Result::setYTable(PointsTable *yTable) {
    Result::yTable = yTable;
}

PointsTable *Result::getZTable() const {
    return zTable;
}

void Result::setZTable(PointsTable *zTable) {
    Result::zTable = zTable;
}

Result::Result(PointsTable *xTable, PointsTable *yTable, PointsTable *zTable) : xTable(xTable), yTable(yTable),
                                                                                zTable(zTable) {}

Result::Result() {}
