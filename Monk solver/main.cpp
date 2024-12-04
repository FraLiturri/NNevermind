#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"

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

    //! Data vector (inputs to Input_Layer);
    Vector<double, 3> data = {3.56, 4.89, 3}; // Creating data vector;
    Vector<double, 2> results = {-289.3456, 212.23};

    //! Demiurge blows;
    Demiurge NeuralNetwork(3, {200, 400, 30}, 2); // input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork;          // pointer to NeuralNetwork;

    //! Printing NN general info:
    print_info(pointerNN);

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden;
    Hidden_Layer second_hidden;
    Hidden_Layer third_hidden;
    Hidden_Layer output_layer;

    //! Output computing and training algorithm;
    for (int n = 0; n < 200; n++)
    {
        input_layer.forward_pass(data);
        first_hidden.forward_pass("linear", 1);
        second_hidden.forward_pass("sigmoid", 2);
        third_hidden.forward_pass("sigmoid", 3);
        output_layer.forward_pass("linear", 4, true);

        output_layer.RandomTraining(results);
    }

    cout << "Final output: " << outputs[weights.size()].transpose() << endl;

    // Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Elapsed time: " << elapsed_time.count() << " seconds.\n"
         << endl;

    return 0;
}
