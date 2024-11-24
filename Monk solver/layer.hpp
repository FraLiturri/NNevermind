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
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

// Defining networks variables;
const int in_units = 2;      // Number of units in input layer; //?For some reasons in. units has to be greater than 1...fix it (it's not that important)
const int out_units = 1;     // Number of units in the output layer;
const int hidden_layers = 3; // Number of hidden layers;

Vector<int, hidden_layers + 1> hidden_and_out_units(1, 2, 3, out_units); // Number of units in each hidden and output layer (last one);
const int training_iterations = 1000; //Number of iterations;

// Creating weights matrices and output vec;
vector<MatrixXd> weights;
vector<VectorXd> outputs;
VectorXd single_output; 

void weights_creator() // Creates weights matrices;
{
    int rows;
    int columns;

    for (int i = 0; i <= hidden_layers + 1; i++)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Defining seed for different random numbers;
        srand(seed);

        i == 0 ? columns = in_units : columns = hidden_and_out_units[i - 1];        // Paying attention to first layer (input);
        i == hidden_layers + 1 ? rows = out_units : rows = hidden_and_out_units[i]; // Paying attention to last layer (output);

        MatrixXd weight = MatrixXd::NullaryExpr(rows, columns, []()
                                                { return Eigen::internal::random<double>(0, 0.5); });
        weight.col(0).setConstant(1); //! Bias terms (Check);
        weights.push_back(weight);    // Storing weights;
        cout << i << " Weights matrix: " << weight << endl;
    }
}

//! Creating Layer classes;
class hidden_Layer
{
public:
    hidden_Layer(string choosen_function, int depth, bool isOutputLayer = false)
    {
        func_choiser(choosen_function);
        isLast = isOutputLayer;
        VectorXd inputs = outputs[depth - 1]; //! Has to be checked;
        for (int k = 0; k < inputs.size(); k++)
        {
            inputs[k] = act_func(inputs[k]); // Making act_function act on input to each unit;
        }
        single_output = weights[depth] * inputs;                // Calculating outputs vector;
        outputs.insert(outputs.begin() + depth, single_output); // Storing outputs;

        // Test: can be deleted after debugging;
        cout << depth << " hidden layer's output: "
             << single_output.transpose() << endl;
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
            cout << "\n";
            for (int i = hidden_layers + 1; i >= 0; i--)
            {
                // Insert BP here, making i flowing from end to start in weights vector;
            }
        }
    }

private:
    bool isLast; // Defined to access isOutputlayer's value;
};

//! Input layer class;
class input_Layer
{
public:
    input_Layer(Vector<double, in_units> input)
    {
        single_output = weights[0] * input;
        outputs.insert(outputs.begin(), single_output);

        // Test: can be deleted after debugging;
        cout << "Input layer's output: "
             << single_output.transpose()
             << endl;
    };
};

#endif