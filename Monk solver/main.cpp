#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"

#include <iostream>
#include <string>
#include <random>
#include <chrono>

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace Eigen;
using namespace std;

int main()
{
    // Counter started;
    auto start = chrono::high_resolution_clock::now();

    //! Initialization part: do not delete (config. settings are in layer.hpp);
    weights_creator(); // Builds the vector containing all the weights (in form of matrices)

    //! Printing config. info:
    print_info(); //Printing NN general info; 

    //! Neural network construction;
    input_Layer Input_Layer({0.23, 3.45});
    hidden_Layer First_hidden("linear", 1);
    hidden_Layer Second_hidden("linear", 2);
    hidden_Layer Third_hidden("linear", 3);
    hidden_Layer Output_Layer("linear", 4, true);

    //! Backpropagation algorithm;
    Output_Layer.BackPropagation();

    // Counter stopped;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Elapsed time: " << elapsed_time.count() << " seconds.\n"
         << endl;

    return 0;
}
