#include "Newton.h"

Newton::Newton() 
    : NofCoef(8), N(361), PI(3.1415926) {
    GenerateData();
    CalcCoef();
    NewtonInterpolate();
    AssignData();
}

/* Generate the data for interpolation */
void Newton::GenerateData() {
    double dt = (2 * PI) / NofCoef;
    for(int i = 0; i < NofCoef; i++) {
        Origin.push_back({
            i * dt,
            i * dt,
            0.0
        });
    }
    std::cout << "Generate Done!\n";
}

void Newton::CalcCoef() {
    const int size = Origin.size();

    {
        coefY = std::vector<std::vector<double>>(size, std::vector<double>(size));
        for (int i = 0; i < Origin.size(); i++) {
            coefY[i][0] = Origin[i].y;
        }

        for (int t = 1; t < NofCoef; t++) {
            for (int j = 0; j < NofCoef - t; j++)
            {
                coefY[j][t] = (coefY[j + 1][t - 1] - coefY[j][t - 1]) / (Origin[j + t].x - Origin[j].x);
            }
        }
        /* Print out coefficient */
        {
            for (int i = 0; i < NofCoef; i++)
            {
                std::cout << "cy[" << i << "] = " << coefY[0][i] << "\n";
            }
            // std::cout << "last = " << coef[0][NofCoef - 1] << std::endl;
        }
    }
    {
        coefX = std::vector<std::vector<double>>(size, std::vector<double>(size));
        for (int i = 0; i < Origin.size(); i++) {
            coefX[i][0] = Origin[i].x;
        }

        for (int t = 1; t < NofCoef; t++) {
            for (int j = 0; j < NofCoef - t; j++)
            {
                coefX[j][t] = (coefX[j + 1][t - 1] - coefX[j][t - 1]) / (Origin[j + t].y - Origin[j].y);
            }
        }
        /* Print out coefficient */
        {
            for (int i = 0; i < NofCoef; i++)
            {
                std::cout << "cx[" << i << "] = " << coefX[0][i] << "\n";
            }
            // std::cout << "last = " << coef[0][NofCoef - 1] << std::endl;
        }
    }
}

double Newton::interpolateY(double x) {
    double sum = coefY[0][NofCoef - 1];

    for(int i = NofCoef - 2; i >= 0; i--) {
        sum = sum * (x - Origin[i].x) + coefY[0][i];
    }

    return sum;
}

double Newton::interpolateX(double y) {
    double sum = coefX[0][NofCoef - 1];

    for(int i = NofCoef - 2; i >= 0; i--) {
        sum = sum * (y - Origin[i].y) + coefX[0][i];
    }

    return sum;
}

void Newton::NewtonInterpolate() {
    value = std::vector<glm::vec3>(N);
    double dt = (2 * PI) / N;
    for(int i = 0; i < N; i++) {
        value[i].x = interpolateX( i * dt );
        value[i].y = interpolateY( i * dt );
        value[i].z = 0.0;
    }
}

void Newton::AssignData() {
    for(int i = 0; i < value.size(); i++) {
        info.vertices.push_back({
            4 * cos( value[i].x ),
            2 * sin( value[i].y ),
            0.0
        });
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

void Newton::draw() const {
    glBindVertexArray(vao);
    glDrawElements(GL_LINES, info.vertexIndices.size(), GL_UNSIGNED_INT, 0);
}