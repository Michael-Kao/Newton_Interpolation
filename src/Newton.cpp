#include "Newton.h"

Newton::Newton() 
    : NofCoef(8), N(361), PI(3.1415926) {
    GenerateData();
    CalcCoef();
}

/* Generate the data for interpolation */
void Newton::GenerateData() {
    double dt = (2 * PI) / NofCoef;
    for(int i = 0; i < NofCoef; i++) {
        Origin.push_back({
            4 * cos( i * dt ),
            2 * sin( i * dt ),
            0.0
        });
    }
    std::cout << "Generate Done!\n";
}

void Newton::CalcCoef() {
    const int size = Origin.size();
    coef = std::vector<std::vector<double>>(size, std::vector<double>(size));
    for(int i = 0; i < Origin.size(); i++) {
        coef[i][0] = Origin[i].y;
    }
    
    for(int t = 1; t < NofCoef; t++) {
        for(int j = 0; j < NofCoef - t; j++) {
            coef[j][t] = (coef[j + 1][t - 1] - coef[j][t - 1]) / (Origin[j + t].x - Origin[j].x);
        }
    }
    /* Print out coefficient */
    {
        for (int i = 0; i < NofCoef; i++) {
            std::cout << "i : " << i << " = " << coef[0][i] << "\n";
        }
    }
}

// double Newton::interpolate(double x) {
//     double sum = coef[0][N - 1];

//     for(int i = 0; i < NofCoef; i++) {

//     }
// }

// void Newton::NewtonInterpolate() {
//     value = std::vector<glm::vec3>(N);
//     double dt = (2 * PI) / N;
//     for(int i = 0; i < N; i++) {
//         value[i].x = 4 * cos( i * dt );
//         value[i].y = interpolate(value[i].x);
//         value[i].z = 0.0;
//     }
// }