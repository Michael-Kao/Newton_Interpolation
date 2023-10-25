#include "Newton.h"

Newton::Newton() 
    : NofCoef(8), N(361), PI(3.1415926) {
    cX = std::vector<std::vector<std::vector<double>>>(6, std::vector<std::vector<double>>(4, std::vector<double>(4)));
    cY = std::vector<std::vector<std::vector<double>>>(6, std::vector<std::vector<double>>(4, std::vector<double>(4)));
    GenerateData();
    CalcCoef();
    NewtonInterpolate();
    AssignData();
    if(NofCoef == 8) {
        splitRegion();
        SplitInterpolate();
        AssignSpline();
    }
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

void Newton::splitRegion() {
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 4; j++) {
            if(j + i < 8) {
                cX[i][j][0] = Origin[j + i].x;
                cY[i][j][0] = Origin[j + i].y;
            }
            else {
                cX[i][j][0] = Origin[0].x;
                cY[i][j][0] = Origin[0].y;
            }
        }
    }

    for(int i = 0; i < 6; i++) {
        for(int t = 1; t < 4; t++) {
            for(int j = 0; j < 4 - t; j++) {
                if(j + t + i == 8) {
                    cY[i][j][t] = (cY[i][j + 1][t - 1] - cY[i][j][t - 1]) / (Origin[0].x - Origin[j + i].x);
                    cX[i][j][t] = (cX[i][j + 1][t - 1] - cX[i][j][t - 1]) / (Origin[0].y - Origin[j + i].y);
                }
                else if(j + i == 8) {
                    cY[i][j][t] = (cY[i][j + 1][t - 1] - cY[i][j][t - 1]) / (Origin[t].x - Origin[0].x);
                    cX[i][j][t] = (cX[i][j + 1][t - 1] - cX[i][j][t - 1]) / (Origin[t].y - Origin[0].y);
                }
                else {
                    cY[i][j][t] = (cY[i][j + 1][t - 1] - cY[i][j][t - 1]) / (Origin[j + t + i].x - Origin[j + i].x);
                    cX[i][j][t] = (cX[i][j + 1][t - 1] - cX[i][j][t - 1]) / (Origin[j + t + i].y - Origin[j + i].y);
                }
            }
        }
    }
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 4; j++) {
            std::cout << "cX[" << i << "][" << j << "] = " << cX[i][0][j] << std::endl;  
        }
    }
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 4; j++) {
            std::cout << "cY[" << i << "][" << j << "] = " << cY[i][0][j] << std::endl;  
        }
    }
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

double Newton::itpX(double y, int section) {
    double sum = cX[section][0][3];
    for(int i = 4 - 2; i >= 0; i--) {
        if(i + section == 8) {
            sum = sum * (y - Origin[0].y) + cX[section][0][i];
        }
        else {
            sum = sum * (y - Origin[i + section].y) + cX[section][0][i];
        }
    }
    return sum;
}

double Newton::itpY(double x, int section) {
    double sum = cY[section][0][3];
    for(int i = 4 - 2; i >= 0; i--) {
        if(i + section == 8) {
            sum = sum * (x - Origin[0].x) + cY[section][0][i];
        }
        else {
            sum = sum * (x - Origin[i + section].x) + cY[section][0][i];
        }
    }
    return sum;
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

void Newton::SplitInterpolate() {
    svalue = std::vector<glm::vec3>(N);
    double dt = (2 * PI) / N;
    for(int i = 0; i < N; i++) {
        if(i < 45)  continue;
        if(i >= 315)    break;
        int idx = i / 45;
        svalue[i].x = itpX( i * dt, idx - 1 );
        svalue[i].y = itpY( i * dt, idx - 1 );
        svalue[i].z = 0.0;
    }
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

void Newton::AssignSpline() {
    for(int i = 45; i < 315; i++) {
        int idx = i / 45 - 1;
        if(i % 45 == 0) {
            spline[idx - 1].vertices.push_back({
                4 * cos( svalue[i].x ),
                2 * sin( svalue[i].y ),
                0.0
            });
        }
        spline[idx].vertices.push_back({
            4 * cos( svalue[i].x ),
            2 * sin( svalue[i].y ),
            0.0
        });
    }
    glGenVertexArrays(6, svao);
    glGenBuffers(6, svbo);
    glGenBuffers(6, sebo);
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < spline[i].vertices.size() - 1; j++) {
            spline[i].vertexIndices.push_back(j);
            spline[i].vertexIndices.push_back(j + 1);
        }
        spline[i].vertexSize = spline[i].vertices.size() * sizeof(glm::vec3);
        spline[i].vertIndicesSize = spline[i].vertexIndices.size() * sizeof(unsigned int);

        glBindVertexArray(svao[i]);
        glBindBuffer(GL_ARRAY_BUFFER, svbo[i]);
        glBufferData(GL_ARRAY_BUFFER, spline[i].vertexSize, spline[i].vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sebo[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, spline[i].vertIndicesSize, spline[i].vertexIndices.data(), GL_STATIC_DRAW);
        
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
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

void Newton::draw(int section) const {
    glBindVertexArray(svao[section]);
    glDrawElements(GL_LINES, spline[section].vertexIndices.size(), GL_UNSIGNED_INT, 0);
}