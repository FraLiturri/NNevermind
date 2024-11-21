#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"

#include <iostream>
#include <string>
#include <random>
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense" //works

using namespace Eigen;
using namespace std;

int main()
{
    //! Initialization part: do not delete (config. settings are in layer.hpp);
    weights_creator(); // Builds the vector containing all the weights (in form of matrices)

    //! Neural network construction;
    input_Layer Input_Layer({1,2,3,4,5,6});
    hidden_Layer First_hidden("threshold", {1,2,3,4}, 1, true); 
    First_hidden.BackPropagation();

    // Printing config. info:
    print_info();

    return 0;
}
