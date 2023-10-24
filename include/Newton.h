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
    std::vector<glm::vec3> value;
private:
    GLuint vao;
    std::vector<std::vector<double>> coefY;
    std::vector<std::vector<double>> coefX;
    // std::vector<double> coef;
    std::vector<glm::vec3> Origin;
    int NofCoef, N;
    double PI;
    double interpolateY(double x);
    double interpolateX(double y);
};