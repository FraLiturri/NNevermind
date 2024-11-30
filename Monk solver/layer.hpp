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
    Hidden_Layer(string choosen_function, int depth, bool isOutputLayer = false)
    {
        func_choiser(choosen_function);
        isLast = isOutputLayer;
        VectorXd inputs = outputs[depth - 1]; //! Has to be checked;

        for (int k = 0; k < inputs.size(); k++)
        {
            inputs[k] = act_func(inputs[k]); // Making act_function act on input to each unit;
        }

        units_output = weights[depth] * inputs;                // Calculating outputs vector;
        outputs.insert(outputs.begin() + depth, units_output); // Storing outputs;
        if (isLast)
        {
            cout << "Final output: " << outputs[depth] << endl;
        }
    }

    void RandomTraining();  // Random training;
    void BackPropagation(); // BackProp. algorithm;

private:
    bool isLast; // Defined to access isOutputlayer's value;
};

//! Input layer class;
class Input_Layer
{
public:
    Input_Layer(VectorXd input)
    {
        units_output = weights[0] * input;
        outputs.insert(outputs.begin(), units_output);
    };
};

void Hidden_Layer::RandomTraining()
{
    if (isLast)
    {
    }
};

#endif