#ifndef demiurge // Checks if unit isn't defined;
#define demiurge // Define unit;

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

// Creating weights matrices and output vec;
vector<MatrixXd> weights;
vector<VectorXd> outputs;
VectorXd single_output;

//! Demiurge class: the Creator;
class Demiurge
{
public:
    int in_units, out_units, hidden_layers;
    int rows, cols;
    vector<int> hidden_and_out_units;

    Demiurge(int inputs_units, vector<int> hidden_units, int output_units)
    {
        in_units = inputs_units;
        out_units = output_units;
        hidden_and_out_units = hidden_units;
        hidden_layers = hidden_units.size();
        hidden_and_out_units.push_back(output_units);

        for (int i = 0; i <= hidden_layers + 1; i++) // This cycle creates weights matrices;
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Defining seed for different random numbers;
            srand(seed);

            i == 0 ? cols = in_units : cols = hidden_and_out_units[i - 1];              // Paying attention to first layer (input);
            i == hidden_layers + 1 ? rows = out_units : rows = hidden_and_out_units[i]; // Paying attention to last layer (output);

            MatrixXd weight = MatrixXd::NullaryExpr(rows, cols, []()
                                                    { return Eigen::internal::random<double>(0, 0.5); });
            weight.col(0).setConstant(1); //! Bias terms (Check);
            weights.push_back(weight);    // Storing weights;
        }
    };
};

#endif