#include "Norm.h"

void NormCalc::Norm2(Analytical *p, Newton *q) {
    double sum = 0.0;
    for(int i = 0; i < p->value.size(); i++) {
        sum +=  (p->value[i].x - q->value[i].x) *
                (p->value[i].x - q->value[i].x) +
                (p->value[i].y - q->value[i].y) *
                (p->value[i].y - q->value[i].y);
    }

    std::cout << "Norm 2 = " << sqrt(sum) << std::endl;
}

void NormCalc::Norminf(Analytical *p, Newton *q) {
    double res = 0.0;
    for(int i = 0; i < p->value.size(); i++) {
        double val = (p->value[i].x - q->value[i].x) *
                    (p->value[i].x - q->value[i].x) +
                    (p->value[i].y - q->value[i].y) *
                    (p->value[i].y - q->value[i].y);
        res =  std::max(res, val);
    }

    std::cout << "Norm infinite = " << res << std::endl;
}