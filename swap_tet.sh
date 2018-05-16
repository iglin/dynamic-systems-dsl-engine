#!/usr/bin/env bash

if [[ -z "taskbag.dpl.cpp" ]] ; then
    mv "taskbag.cpp" "taskbag.dpl.cpp"
    mv "taskbag.dsg.cpp" "taskbag.cpp"
else
    mv "taskbag.cpp" "taskbag.dsg.cpp"
    mv "taskbag.dpl.cpp" "taskbag.cpp"
fi