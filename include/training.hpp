#ifndef training
#define training

#include "layer.hpp"
#include "demiurge.hpp"
#include "activation_functions.hpp"
#include "eigen_path.hpp"
#include "lib.hpp"

using namespace std;
using namespace Eigen;

double delta_k = 0;
double beta_1 = 0.9, beta_2 = 0.999;
int i, size = 0;

VectorXd net_calculator(int layer_number)
{
    net = weights[layer_number - 1] * outputs[layer_number - 1];
    return net;
};

void BackPropagation(VectorXd &d, double &eta, double alpha = 0, double lambda = 0)
{
    i = weights.size();
    while (i > 0)
    {
        if (i == weights.size())
        {
            func_choiser(function_strings[i - 1]);
            net_t = net_calculator(i);

            delta.conservativeResize(d.size());
            for (int k = 0; k < d.size(); k++)
            {
                delta_k = (d[k] - outputs[i][k]) * der_act_func(net_t[k]);
                delta[k] = delta_k;
            }

            if (prev_updates[0](0, 0) == 0) // The first element is 0 only at initialization; after is always 1 (bias term);
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1];
            }
            else
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1] + alpha * prev_updates[i - 1];
            }

            weights[i - 1] = weights[i - 1] + update;
            prev_updates[i - 1] = update;
        }

        else
        {
            net_t = net_calculator(i);
            func_choiser(function_strings[i - 1]);
            delta = weights[i].transpose() * delta;

            for (int k = 0; k < delta.size(); k++)
            {
                delta[k] = delta[k] * der_act_func(net_t[k]);
            }

            if (prev_updates[0](0, 0) == 0)
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1];
            }
            else
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1] + alpha * prev_updates[i - 1];
            }

            weights[i - 1] = weights[i - 1] + update;
            prev_updates[i - 1] = update;
        }
        i--;
    };
}
void RandomTraining(VectorXd &d, double &eta, double alpha = 0, double lambda = 0)
{
    i = weights.size();
    if (i == weights.size())
    {
        func_choiser(function_strings[i - 1]);
        net_t = net_calculator(i);

        delta.conservativeResize(d.size());
        for (int k = 0; k < d.size(); k++)
        {
            delta_k = (d[k] - outputs[i][k]) * der_act_func(net_t[k]);
            delta[k] = delta_k;
        }

        if (prev_updates[0](0, 0) == 0) // The first element is 0 only at initialization; after is always 1 (bias term);
        {
            update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1];
        }
        else
        {
            update = eta * delta * outputs[i - 1].transpose() - lambda * weights[i - 1] + alpha * prev_updates[i - 1];
        }

        weights[i - 1] = weights[i - 1] + update;
        prev_updates[i - 1] = update;
    }
}
void Adam(VectorXd &d, double &eta, double alpha = 0, double lambda = 0)
{
    i = weights.size(); 
    while (i > 0)
    {
        if (i == weights.size())
        {
            func_choiser(function_strings[i - 1]);
            net_t = net_calculator(i);
            delta.conservativeResize(d.size());

            for (int k = 0; k < d.size(); k++)
            {
                delta_k = (d[k] - outputs[i][k]) * der_act_func(net_t[k]);
                delta[k] = delta_k;
            }

            gradient = delta * outputs[i - 1].transpose();          // calculating gradient with BP formula.
            gradient_square = (gradient.array().square()).matrix(); // elementwise square;

            M_t[i - 1] = M_t[i - 1] * beta_1 + (1 - beta_1) * gradient;
            V_t[i - 1] = V_t[i - 1] * beta_2 + (1 - beta_2) * gradient_square;

            M_hat = M_t[i - 1] / (double)(1 - pow(beta_1, adam_counter));
            V_hat = V_t[i - 1] / (double)(1 - pow(beta_2, adam_counter));

            sqrt_v = V_hat.array().sqrt();
            sqrt_v = sqrt_v.array() + epsilon;

            update = M_hat.array() / sqrt_v.array();                                  // calculating update to the weight;
            weights[i - 1] = weights[i - 1] + eta * update - lambda * weights[i - 1]; // L2 reg. added;
        }

        else
        {
            net_t = net_calculator(i);
            func_choiser(function_strings[i - 1]);

            delta = weights[i].transpose() * delta;

            for (int k = 0; k < delta.size(); k++)
            {
                delta[k] = delta[k] * der_act_func(net_t[k]);
            }

            gradient = delta * outputs[i - 1].transpose();
            gradient_square = gradient.array().square();

            M_t[i - 1] = M_t[i - 1] * beta_1 + (1 - beta_1) * gradient;
            V_t[i - 1] = V_t[i - 1] * beta_2 + (1 - beta_2) * gradient_square;

            M_hat = M_t[i - 1] / (double)(1 - pow(beta_1, adam_counter));
            V_hat = V_t[i - 1] / (double)(1 - pow(beta_2, adam_counter));

            sqrt_v = V_hat.array().sqrt();
            sqrt_v = sqrt_v.array() + epsilon;

            update = (M_hat.array() / sqrt_v.array()).matrix();
            weights[i - 1] = weights[i - 1] + eta * update - lambda * weights[i - 1];
        }
        i--;
    };
}

#endif