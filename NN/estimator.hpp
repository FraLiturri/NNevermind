#ifndef estimator
#define estimator

#include "lib.hpp"
#include "demiurge.hpp"
#include "validation.hpp"

double ex_time;
double n_weights = 1;

void Estimator(int iter)
{
    for (int k = 0; k < hidden_and_out_units.size(); k++)
    {
        n_weights *= hidden_and_out_units[k];
    }
    ex_time = 2 * 2 * log10(200) * iter / (double)100 * exp(n_weights * 0.0001);
}

#endif