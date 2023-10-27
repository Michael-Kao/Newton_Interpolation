#pragma once

#include "Object.h"
#include <iomanip>
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
    int NofCoef, N;
private:
    GLuint vao;
    GLuint svao[6];
    std::vector<std::vector<double>> coefY;
    std::vector<std::vector<double>> coefX;
    std::vector<std::vector<std::vector<double>>> cX;
    std::vector<std::vector<std::vector<double>>> cY;
    // std::vector<double> coef;
    std::vector<glm::vec3> OriginX;
    std::vector<glm::vec3> OriginY;
    double PI;
    double interpolateY(double x);
    double interpolateX(double x);
    double itpX(double x, int section);
    double itpY(double x, int section);
    void c1Continuity(int section, double val);
    void splitRegion();
};