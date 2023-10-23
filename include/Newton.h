#pragma once

#include "Object.h"
#include <cmath>

class Newton {
public:
    Newton();
    void CalcCoef();
    void GenerateData();
    void NewtonInterpolate();
    void AssignData();
    struct ObjectInfo info;
    GLuint vbo, ebo;
    void draw() const;
private:
    GLuint vao;
    std::vector<std::vector<double>> coefY;
    std::vector<std::vector<double>> coefX;
    // std::vector<double> coef;
    std::vector<glm::vec3> Origin;
    std::vector<glm::vec3> value;
    int NofCoef, N;
    double PI;
    double interpolateY(double x);
    double interpolateX(double y);
};