#pragma once

#include "../global.h"
#include "../extremePoint/extremePoint.h"

class moeaSubProblem{
public:
    moeaSubProblem(){}
    ~moeaSubProblem(){weight.clear();neighbor.clear();}

    vector<double> weight;
    vector<unsigned int> observe;
    vector<unsigned int> neighbor;
    /// My class name.
    virtual std::string className() const
    {
        return "moeaSubProblem";
    }
};

