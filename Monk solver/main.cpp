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

    //! Printing config. info:
    print_info();

    //! Neural network construction;
    input_Layer Input_Layer({1,2});
    hidden_Layer First_hidden("linear", 1);
    hidden_Layer Second_hidden("linear", 2, true); 
    Second_hidden.BackPropagation();

    return 0;
}
