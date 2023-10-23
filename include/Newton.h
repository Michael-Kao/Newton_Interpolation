#pragma once

#include "Object.h"
#include <cmath>

class Newton {
public:
    Newton();
    void CalcCoef();
    void GenerateData();
    void NewtonInterpolate();
private:
    std::vector<std::vector<double>> coef;
    std::vector<glm::vec3> Origin;
    std::vector<glm::vec3> value;
    int NofCoef, N;
    double PI;
    double interpolate(double x);
};