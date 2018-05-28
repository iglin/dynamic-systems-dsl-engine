#include <iostream>
#include <list>
#include "InitialData.h"
#include "EulersMethod.h"
#include "RungeKuttaMethod.h"
#include "ExportUtils.h"
#include "HeunsMethod.h"
#include "SimpsonsMethod.h"
#include "Extrapolation.h"
#include "DormandPrinceMethod.h"
#include "ProgramExecutor.h"

using namespace std;

int main() {
    ProgramExecutor::execute();
    return 0;
}