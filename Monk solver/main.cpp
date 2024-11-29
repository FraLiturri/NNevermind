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
    // Counter starts;
    auto start = chrono::high_resolution_clock::now();

    //! Initialization part: do not delete (config. settings are in layer.hpp);
    Vector<double, 2> data = {1, 2}; // Creating data vector;

    //! Demiurge blows;
    Demiurge NN(2, {1}, 1);
    Demiurge *pointerNN = &NN;

    //! Printing config. info:
    print_info(pointerNN); // Printing NN general info;

    //! Neural network construction;
    Input_Layer Input_Layer(data);
    Hidden_Layer First_hidden("linear", 1);
    Hidden_Layer Output_Layer("linear", 2, true);

    //! Backpropagation algorithm;
    Output_Layer.BackPropagation();

    // Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Elapsed time: " << elapsed_time.count() << " seconds.\n"
         << endl;

    return 0;
}
