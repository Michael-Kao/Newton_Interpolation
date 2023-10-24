#include "Analytic.h"


Analytical::Analytical() 
    : PI(3.1415926) {
    double dt = (2 * PI) / 360.0;

    for(int i = 0; i < 361; i++) {
        value.push_back({
            i * dt,
            i * dt,
            0.0
        });
        info.vertices.push_back( { 4 * cos( i * dt ), 
                                   2 * sin( i * dt ), 
                                   0.0 });
    }
    for(int i = 0; i < info.vertices.size() - 1; i++) {
        info.vertexIndices.push_back(i);
        info.vertexIndices.push_back(i + 1);
    }

    info.vertexSize = info.vertices.size() * sizeof(glm::vec3);
    info.vertIndicesSize = info.vertexIndices.size() * sizeof(unsigned int);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, info.vertexSize, info.vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, info.vertIndicesSize, info.vertexIndices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
}

void Analytical::draw() const {
    glBindVertexArray(vao);
    glDrawElements(GL_LINES, info.vertexIndices.size(), GL_UNSIGNED_INT, 0);
}