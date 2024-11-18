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
    weights_creator(); // Builds the vector containing all the weights (in form of matrices)

    //! Neural network construction;
    for (int j = 0; j < weights.size(); j++)
    {
        cout << weights[j] << endl
             << endl;
    }

    input_Layer input_Layer({1,2,3,4,5,6});
    input_Layer.outputs_getter(); 

    // Printing config. info:
    print_info();

    return 0;
}
