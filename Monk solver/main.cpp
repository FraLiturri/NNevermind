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
    counter();         // Counts how many units have been used;
    weights_creator(); // Builds the vector containing all the weights (in form of matri

    //! Neural network construction;
    Layer("linear", {0, 0, 3}); // test printing act_func(double);
    input_Layer({0, 1});

    for (int j = 0; j < weights.size(); j++)
    {
        cout << weights[j] << endl
             << endl;
    }

    // Printing config. info:
    print_info();
    return 0;
}
