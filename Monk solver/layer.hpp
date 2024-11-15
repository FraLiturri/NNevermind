#ifndef layer // Checks if unit isn't defined;
#define layer // Define unit;

#include <iostream>
#include <fstream>
#include <string>
#include "activation_functions.hpp"
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense" //works

using namespace std;
using namespace Eigen;

// Defining networks variables;
int hidden_layers = 1;
int in_units = 6;
int out_units = 6;

Vector2d hidden_units = {6, 3}; // Each component represents the numbers of unit in each HIDDEN layer;

// Tot number of units;
int units = 1;
int number()
{
    for (int i = 0; i < hidden_units.size(); i++)
    {
        units += hidden_units[i];
    }
    units = units * in_units * out_units;
    return units;
}

VectorXd weights(units);

double Layer(string function_choosen, Vector3d input) //In future has to return a vector;
{
    func_choiser(function_choosen); //! use act_func as working tool [e.g. act_func(2.3)];
    return 0;
}

double inLayer(VectorXd input) //Input layer; 
{
    return 0;
}

#endif