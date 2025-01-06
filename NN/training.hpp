#ifndef training
#define training

#include "layer.hpp"
#include "demiurge.hpp"
#include "activation_functions.hpp"

#include <any>
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

VectorXd delta, net_t, net, vec_aux;
vector<VectorXd> storer;
MatrixXd update, auxiliar, prev_weight;

double delta_k; // auxiliar double;
int i, size;

VectorXd net_calculator(int layer_number)
{
    net = weights[layer_number - 1] * outputs[layer_number - 1];
    return net;
};

void Hidden_Layer::BackPropagation(variant<double, VectorXd> d, double eta, double alpha = 0, double lambda = 0)
{
    i = weights.size();
    while (i > 0)
    {
        prev_weight = weights[i - 1]; // For Tikhonov regularization;
        if (i == weights.size())
        {
            func_choiser(function_strings[i - 1]);
            net_t = net_calculator(i);

            if (holds_alternative<double>(d))
            {
                delta.conservativeResize(1);
                for (int k = 0; k < 1; k++)
                {
                    delta_k = (get<double>(d) - outputs[i][k]) * der_act_func(net_t[k]);
                    delta[k] = delta_k;
                }
            }
            else if (holds_alternative<VectorXd>(d))
            {
                delta.conservativeResize(get<VectorXd>(d).size());
                for (int k = 0; k < get<VectorXd>(d).size(); k++)
                {
                    delta_k = (get<VectorXd>(d)[k] - outputs[i][k]) * der_act_func(net_t[k]);
                    delta[k] = delta_k;
                }
            }
            else
            {
                throw runtime_error("Backpropagation accepts only double or VectorXd as first input.");
            }

            if (prev_updates[0](0, 0) == 0) // The first element is 0 only at initialization; after is always 1 (bias term);
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight;
            }
            else
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight + alpha * prev_updates[i - 1];
            }

            update = eta * delta * outputs[i - 1].transpose();

            weights[i - 1] = weights[i - 1] + update;
            weights[i - 1].col(0).setConstant(1);

            prev_updates[i - 1] = update;
            storer.push_back(delta);
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
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight;
            }
            else
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight + alpha * prev_updates[i - 1];
            }

            weights[i - 1] = weights[i - 1] + update;
            weights[i - 1].col(0).setConstant(1);

            prev_updates[i - 1] = update;
            storer.push_back(delta);
        }
        i--;
    };

    function_strings.clear();
    next_inputs.clear();
    units_output.setZero();
}
void Hidden_Layer::RandomTraining(variant<double, VectorXd> d, double eta, double alpha = 0, double lambda = 0)
{
    i = weights.size();
    prev_weight = weights[i - 1]; // For Tikhonov regularization;
    if (i == weights.size())
    {
        func_choiser(function_strings[i - 1]);
        net_t = net_calculator(i);

        if (holds_alternative<double>(d))
        {
            delta.conservativeResize(1);
            for (int k = 0; k < 1; k++)
            {
                delta_k = (get<double>(d) - outputs[i][k]) * der_act_func(net_t[k]);
                delta[k] = delta_k;
            }
        }
        else if (holds_alternative<VectorXd>(d))
        {
            delta.conservativeResize(get<VectorXd>(d).size());
            for (int k = 0; k < get<VectorXd>(d).size(); k++)
            {
                delta_k = (get<VectorXd>(d)[k] - outputs[i][k]) * der_act_func(net_t[k]);
                delta[k] = delta_k;
            }
        }
        else
        {
            throw runtime_error("Backpropagation accepts only double or VectorXd as first input.");
        }

        if (prev_updates[0](0, 0) == 0) // The first element is 0 only at initialization; after is always 1 (bias term);
        {
            update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight;
        }
        else
        {
            update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight + alpha * prev_updates[i - 1];
        }

        weights[i - 1] = weights[i - 1] + update;
        weights[i - 1].col(0).setConstant(1);

        prev_updates[i - 1] = update;
        storer.push_back(delta);
    }

    function_strings.clear();
    next_inputs.clear();
    units_output.setZero();
}
void Hidden_Layer::RMSprop(variant<double, VectorXd> d, double eta, double alpha, double lambda)
{
    i = weights.size();
    while (i > 0)
    {
        prev_weight = weights[i - 1]; // For Tikhonov regularization;
        if (i == weights.size())
        {
            delta.setZero();
            func_choiser(function_strings[i - 1]);
            net_t = net_calculator(i);

            if (holds_alternative<double>(d))
            {
                for (int k = 0; k < 1; k++)
                {
                    delta.conservativeResize(k + 1);
                    delta_k = (get<double>(d) - outputs[i][k]) * der_act_func(net_t[k]);
                    delta[k] = delta_k;
                }
            }
            else if (holds_alternative<VectorXd>(d))
            {
                for (int k = 0; k < get<VectorXd>(d).size(); k++)
                {
                    delta.conservativeResize(k + 1);
                    delta_k = (get<VectorXd>(d)[k] - outputs[i][k]) * der_act_func(net_t[k]);
                    delta[k] = delta_k;
                }
            }

            if (prev_updates[0](0, 0) == 0) // The first element is 0 only at initialization; after is always 1 (bias term);
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight;
            }
            else
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight + alpha * prev_updates[i - 1];
            }

            weights[i - 1] = weights[i - 1] + update;
            weights[i - 1].col(0).setConstant(1);
            prev_updates[i - 1] = update;
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

            if (prev_updates[0](0, 0) == 0)
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight;
            }
            else
            {
                update = eta * delta * outputs[i - 1].transpose() - lambda * prev_weight + alpha * prev_updates[i - 1];
            }

            weights[i - 1] = weights[i - 1] + update;
            weights[i - 1].col(0).setConstant(1);
            prev_updates[i - 1] = update;

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

#endif