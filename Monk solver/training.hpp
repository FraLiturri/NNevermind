#ifndef training
#define training

#include "layer.hpp"
#include "demiurge.hpp"
#include "activation_functions.hpp"
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

#include <iostream>
#include <vector>

using namespace std;
using namespace Eigen;

VectorXd delta, net_t;
vector<VectorXd> storer;

VectorXd net_calculator(int layer_number)
{
    VectorXd net = weights[layer_number - 1] * outputs[layer_number - 1];
    return net;
};

void Hidden_Layer::BackPropagation(VectorXd d)
{
    double eta = 0.05;
    VectorXd net_t;
    delta.setZero();

    int i = weights.size(); // Runs over wieghts matrices;
    while (i > 0)
    {
        if (i == weights.size())
        {
            func_choiser(function_strings[i - 1]);
            net_t = net_calculator(i);

            for (int k = 0; k < d.size(); k++)
            {
                delta.conservativeResize(k + 1);
                double delta_k = (d[k] - outputs[i][k]) * der_act_func(net_t[k]);
                delta(k) = delta_k;
            }

            VectorXd update = delta * outputs[i - 1].transpose();
            weights[i - 1] = weights[i - 1] + eta * update;
            weights[i - 1].col(0).setConstant(1);
        }
        i--;
    };
}

void Hidden_Layer::RandomTraining(VectorXd d)
{
    double eta = 0.05;
    int i = weights.size();
    delta.setZero();

    func_choiser(function_strings[i - 1]);
    net_t = net_calculator(i);

    for (int k = 0; k < d.size(); k++)
    {
        delta.conservativeResize(k + 1);
        double delta_k = (d[k] - outputs[i][k]) * der_act_func(net_t[k]);
        delta[k] = delta_k;
    }

    MatrixXd update = delta * outputs[i-1].transpose();

    weights[i - 1] = weights[i - 1] + eta * update;
    weights[i - 1].col(0).setConstant(1);
}

#endif