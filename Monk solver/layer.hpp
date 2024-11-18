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
const int in_units = 6;      // Number of units in input layer;
const int out_units = 2;     // Number of units in the output layer;
const int hidden_layers = 2; // Number of hidden layers;

Vector<int, hidden_layers> hidden_units(4, 5); // Each component represents the numbers of unit in each HIDDEN layer;
                                               // In case of bigger networks, change to VectorXd (specifing the size)
                                               // and put hidden_units << -your units list- in main(){};

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

// Creating weights matrices and output vec;
vector<MatrixXd> weights;
void weights_creator()
{
    int rows;
    int columns;
    for (int i = 0; i <= hidden_layers; i++)
    {
        i == 0 ? columns = in_units : columns = hidden_units[i - 1];    // Paying attention to first layer (input);
        i == hidden_layers ? rows = out_units : rows = hidden_units[i]; // Paying attention to last layer (output);

        MatrixXd weight(rows, columns);        // Creating matrix;
        weights.push_back(weight.setConstant(1)); // Storing weights;
    }
}

// General hidden layer; //? Has to be converted into a class?;
double Layer(string function_choosen, Vector3d input) // In future has to return a vector;
{
    func_choiser(function_choosen); //! use act_func as working tool [e.g. act_func(2.3)];
    return 0;
}

//Creating input_Layer class; 
class input_Layer
{
private:
    vector<VectorXd> outputs; // Specific the size of the vector when possible;

public:
    input_Layer(Vector<double, in_units> input)
    {

        for (int k = 0; k < in_units; k++)
        {
            VectorXd output = weights[0] * input;
            outputs.push_back(output); 
        }
    };

    vector<VectorXd> output_getter()
    {
        cout << outputs[0];
        return outputs;
    };
};

#endif