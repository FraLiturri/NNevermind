#ifndef layer // Checks if unit isn't defined;
#define layer // Define unit;

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "activation_functions.hpp"
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense" //works

using namespace std;
using namespace Eigen;

// Defining networks variables;
const int in_units = 1;  // Number of units in input layer;
const int out_units = 2; // Number of units in the output layer;
int hidden_layers = 3;   // Number of hidden layers;

VectorXd hidden_units(hidden_layers); // Each component represents the numbers of unit in each HIDDEN layer;

// How many units?
double tot_units;
double counter()
{
    double count = 1;
    for (int i = 0; i < hidden_units.size(); i++)
    {
        count *= hidden_units[i];
    }
    tot_units = count * in_units * out_units;
    return tot_units;
}

// Creating weights matrices;
vector<MatrixXd> weights; 
void weights_creator()
{
    int rows;
    int columns;
    for (int i = 0; i < hidden_layers +1; i++)
    {
        i == 0 ? columns = in_units : columns = hidden_units[i - 1];    // Paying attention to first layer (input);
        i == hidden_layers ? rows = out_units : rows = hidden_units[i]; // Paying attention to last layer (output);

        MatrixXd weight(rows, columns);
        weights.push_back(weight.setRandom());
    }
}

// General hidden layer;
double Layer(string function_choosen, Vector3d input) // In future has to return a vector;
{
    func_choiser(function_choosen); //! use act_func as working tool [e.g. act_func(2.3)];
    return 0;
}

// Input layer;
double input_Layer(VectorXd input) // Input layer;
{
    int next_units = int(hidden_units[0]);
    VectorXd output_0(next_units);
    for (int i = 0; i < int(hidden_units[0]); i++)
    {
        output_0[i] = 1;
    }
    return 0;
}

#endif