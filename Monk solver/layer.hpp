#ifndef layer // Checks if unit isn't defined;
#define layer // Define unit;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

#include "activation_functions.hpp"
#include "demiurge.hpp"

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

//! Creating Layer classes;
class Hidden_Layer
{
public:
    int hidden_layers;
    Hidden_Layer(string choosen_function, int depth, Demiurge *pointer, bool isOutputLayer = false)
    {
        func_choiser(choosen_function);
        hidden_layers = pointer->hidden_layers;
        isLast = isOutputLayer;
        VectorXd inputs = outputs[depth - 1]; //! Has to be checked;

        for (int k = 0; k < inputs.size(); k++)
        {
            inputs[k] = act_func(inputs[k]); // Making act_function act on input to each unit;
        }

        single_output = weights[depth] * inputs;                // Calculating outputs vector;
        outputs.insert(outputs.begin() + depth, single_output); // Storing outputs;
        if (isLast)
        {
            cout << "Final output: " << outputs[depth] << endl;
        }
    }

    void RandomTraining() // Random training;
    {
        if (isLast)
        {
        }
    }

    void BackPropagation() // BackProp. algorithm;
    {
        if (isLast)
        {
            for (int i = hidden_layers + 1; i >= 0; i--)
            {
                cout << "Testing";
            }
        }
    }

private:
    bool isLast; // Defined to access isOutputlayer's value;
};

//! Input layer class;
class Input_Layer
{
public:
    Input_Layer(VectorXd input)
    {
        single_output = weights[0] * input;
        outputs.insert(outputs.begin(), single_output);
    };
};

#endif