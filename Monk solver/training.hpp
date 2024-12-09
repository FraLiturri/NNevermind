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
vector<MatrixXd> prev_updates;

VectorXd net_calculator(int layer_number)
{
    VectorXd net = weights[layer_number - 1] * outputs[layer_number - 1];
    return net;
};

void Hidden_Layer::BackPropagation(double d, double eta = 0.05, double alpha = 0, double lambda = 0)
{
    MatrixXd update, auxiliar;
    double delta_k = 0;     // auxiliar double;
    int i = weights.size(); // Runs over wieghts matrices;

    while (i > 0)
    {
        if (i == weights.size())
        {
            delta.setZero();
            func_choiser(function_strings[i - 1]);
            net_t = net_calculator(i);

            for (int k = 0; k < 1; k++)
            {
                delta.conservativeResize(k + 1);
                delta_k = (d - outputs[i][k]) * der_act_func(net_t[k]);
                delta[k] = delta_k;
            }

            update = delta * outputs[i - 1].transpose();
            weights[i - 1] = weights[i - 1] + eta * update;
            // weights[i - 1].col(0).setConstant(1);

            storer.push_back(delta);
        }

        else
        {
            delta.setZero();
            func_choiser(function_strings[i - 1]);

            auxiliar = weights[i];
            net_t = net_calculator(i);

            delta = storer[weights.size() - (i + 1)].transpose() * auxiliar;

            for (int k = 0; k < delta.size(); k++)
            {
                delta[k] = delta[k] * der_act_func(net_t[k]);
            }

            update = delta * outputs[i - 1].transpose();
            weights[i - 1] = weights[i - 1] + eta * update;
            // weights[i - 1].col(0).setConstant(1);

            storer.push_back(delta);
        }

        if (i == 1)
        {
            outputs.clear();
            next_inputs.clear();
            function_strings.clear();
            storer.clear();
        }

        i--;
    };
}

void Hidden_Layer::RandomTraining(double d, double eta, double alpha = 0, double lambda = 0)
{

    MatrixXd update;
    double delta_k = 0; // auxiliar double;
    int i = weights.size();
    delta.setZero();

    func_choiser(function_strings[i - 1]);
    net_t = net_calculator(i);

    for (int k = 0; k < 1; k++)
    {
        delta.conservativeResize(k + 1);
        delta_k = (d - outputs[i][k]) * der_act_func(net_t[k]);
        delta[k] = delta_k;
    }

    update = delta * outputs[i - 1].transpose();
    weights[i - 1] = weights[i - 1] + eta * update;
    // weights[i - 1].col(0).setConstant(1);

    function_strings.clear();
    outputs.clear();
    next_inputs.clear();
    units_output.setZero();
}

#endif