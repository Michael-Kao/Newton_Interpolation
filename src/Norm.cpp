#include "Norm.h"

void NormCalc::Norm2(Analytical *p, Newton *q) {
    double sum = 0.0, cur_max = 0.0;
    int idx;
    for(int i = 0; i < p->value.size(); i++) {
        double val;
        val  =  (p->value[i].x - q->value[i].x) *
                (p->value[i].x - q->value[i].x) +
                (p->value[i].y - q->value[i].y) *
                (p->value[i].y - q->value[i].y);
        if(val > cur_max) {
            cur_max = std::max(cur_max, val);
            idx = i;
        }
        sum += val;
    }

    std::cout << "Norm 2 = " << sqrt(sum) << " Max at " << idx << std::endl;
}

void NormCalc::Norminf(Analytical *p, Newton *q) {
    int idx, m_pos;
    double res = 0.0, cur_min = DBL_MAX;
    for(int i = 0; i < p->value.size(); i++) {
        double val =(p->value[i].x - q->value[i].x) *
                    (p->value[i].x - q->value[i].x) +
                    (p->value[i].y - q->value[i].y) *
                    (p->value[i].y - q->value[i].y);
        if(res < val) {
            res =  std::max(res, val);
            idx = i;
        }
        if(val < cur_min) {
            cur_min = val;
            m_pos = i;
        }
    }

    std::cout << "Norm infinite = " << res << " at " << idx << " min = " << cur_min << " at " << m_pos << std::endl;
}

void NormCalc::Norm2(Analytical *p, Newton *q, int section) {
    if(q->NofCoef > 9)  return;
    double sum = 0.0, cur_max = 0.0;
    int pos;
    for(int i = 45 * (section + 1); i < 45 * (section + 2); i++) {
        double val;
        int idx = i % 45;
        val =   (p->value[i].x - q->svalue[i].x) *
                (p->value[i].x - q->svalue[i].x) +
                (p->value[i].y - q->svalue[i].y) *
                (p->value[i].y - q->svalue[i].y);
        
        if(val > cur_max) {
            cur_max = val;
            pos = i % 45;
        }
        sum += val;
    }

    std::cout << "Norm 2 in section " << section + 1 << " = " << sum << " Max at " << pos << std::endl;
}

void NormCalc::Norminf(Analytical *p, Newton *q, int section) {
    if(q->NofCoef > 9)  return;
    double res = 0.0;
    int pos;
    for(int i = 45 * (section + 1); i < 45 * (section + 2); i++) {
        double val;
        int idx = i % 45;
        val =   (p->value[i].x - q->svalue[i].x) *
                (p->value[i].x - q->svalue[i].x) +
                (p->value[i].y - q->svalue[i].y) *
                (p->value[i].y - q->svalue[i].y);
        
        if(val > res) {
            res = val;
            pos = i % 45;
        }
    }

    std::cout << "Norm infinite in section " << section + 1 << " = " << res << " at " << pos << std::endl;
}