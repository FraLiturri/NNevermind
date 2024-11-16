#include "layer.hpp"
#include "activation_functions.hpp"
#include <iostream>
#include <string>
#include <random>
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense" //works

using namespace Eigen;
using namespace std;

int main()
{
    //! Initialization part: do not delete;
    hidden_units << 1, 2, 3, 4; // Number of units in each hidden layer;
    counter();                  // Counts how many units have been used;

    matrix << 1, 2, 3, 4, 5, 6;

    VectorXd Rex = matrix.reshaped();
    cout << Rex;

    // Neural network construction;
    Layer("linear", {0, 0, 3}); // test printing act_func(double);
    input_Layer({0, 1});
    return 0;
}
