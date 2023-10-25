#include "Norm.h"

void NormCalc::Norm2(Analytical *p, Newton *q) {
    double sum = 0.0;
    int idx;
    for(int i = 0; i < p->value.size(); i++) {
        double val;
        val  =  (p->value[i].x - q->value[i].x) *
                (p->value[i].x - q->value[i].x) +
                (p->value[i].y - q->value[i].y) *
                (p->value[i].y - q->value[i].y);
        if(val > sum) {
            sum = std::max(sum, val);
            idx = i;
        }
    }

    std::cout << "Norm 2 = " << sqrt(sum) << " Max at " << idx << std::endl;
}

void NormCalc::Norminf(Analytical *p, Newton *q) {
    int idx;
    double res = 0.0;
    for(int i = 0; i < p->value.size(); i++) {
        double val =(p->value[i].x - q->value[i].x) *
                    (p->value[i].x - q->value[i].x) +
                    (p->value[i].y - q->value[i].y) *
                    (p->value[i].y - q->value[i].y);
        if(res < val) {
            res =  std::max(res, val);
            idx = i;
        }
    }

    std::cout << "Norm infinite = " << res << " at " << idx << std::endl;
}