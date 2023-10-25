#pragma once

#include "Object.h"
#include <cmath>

/* TODO: seperate Newton interpolation 6 times */

class Newton {
public:
    Newton();
    void CalcCoef();
    void GenerateData();
    void NewtonInterpolate();
    void SplitInterpolate();
    void AssignData();
    void AssignSpline();
    struct ObjectInfo info;
    struct ObjectInfo spline[6];
    GLuint vbo, ebo;
    GLuint svbo[6], sebo[6];
    void draw() const;
    void draw(int section) const;
    std::vector<glm::vec3> value;
    std::vector<glm::vec3> svalue;
private:
    GLuint vao;
    GLuint svao[6];
    std::vector<std::vector<double>> coefY;
    std::vector<std::vector<double>> coefX;
    std::vector<std::vector<std::vector<double>>> cX;
    std::vector<std::vector<std::vector<double>>> cY;
    // std::vector<double> coef;
    std::vector<glm::vec3> Origin;
    int NofCoef, N;
    double PI;
    double interpolateY(double x);
    double interpolateX(double y);
    double itpX(double y, int section);
    double itpY(double x, int section);
    void splitRegion();
};