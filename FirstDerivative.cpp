//
// Created by root on 10/17/17.
//

#include "FirstDerivative.h"

FirstDerivative::FirstDerivative() = default;

FirstDerivative::FirstDerivative(InitialData *initialData) : initialData(initialData) {}

InitialData *FirstDerivative::getInitialData() const {
    return initialData;
}

void FirstDerivative::setInitialData(InitialData *initialData) {
    FirstDerivative::initialData = initialData;
}
