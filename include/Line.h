#pragma once 

#include "Object.h"

class Line : public Object {
public:
    Line();
    void drawLine() const;
private:
    GLuint vao;
};