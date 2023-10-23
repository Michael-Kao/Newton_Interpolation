#pragma once

#include "Object.h"
#include <cmath>

class Analytical {
public:
    Analytical();
    GLuint vbo, ebo;
    struct ObjectInfo info;
    void draw() const;
private:
    GLuint vao;
    double PI;
};