#pragma once

#include "Newton.h"
#include "Analytic.h"
#include <iostream>
#include <cmath>
#include <climits>

struct NormCalc{
    void Norm2(Analytical *p, Newton *q);
    void Norminf(Analytical *p, Newton *q);
    void Norm2(Analytical *p, Newton *q, int section);
    void Norminf(Analytical *p, Newton *q, int section);
};