//
// Created by alex on 02.06.18.
//

#ifndef DYNAMIC_SYSTEMS_DSL_CHARTPOINTS_H
#define DYNAMIC_SYSTEMS_DSL_CHARTPOINTS_H

#include <string>

using namespace std;

class ChartPoints {
public:
    virtual string toJson() = 0;
};
#endif //DYNAMIC_SYSTEMS_DSL_CHARTPOINTS_H
