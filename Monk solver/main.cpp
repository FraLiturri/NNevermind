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
    Vector<double, 3> data = {3.56, 4.89, 3};      // Creating data vector;
    Vector<double, 2> results = {20.39, -1.34}; // Expected results;

    //! Demiurge blows;
    Demiurge NeuralNetwork(3, {20, 40, 25, 30, 20, 12}, 2); // Input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork;         // Pointer to NeuralNetwork, avoidable if not desired;

    // Printing NN general info: can be avoided if not desired;
    print_info(pointerNN);

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden;
    Hidden_Layer second_hidden;
    Hidden_Layer third_hidden;
    Hidden_Layer fourth_hidden; 
    Hidden_Layer fifth_hidden;
    Hidden_Layer sixth_hidden;
    Hidden_Layer output_layer;

    //! Output computing and training algorithm;
    for (int n = 0; n < 6000; n++)
    {
        input_layer.forward_pass(data);
        first_hidden.forward_pass("linear", 1);
        second_hidden.forward_pass("sigmoid", 2);
        third_hidden.forward_pass("sigmoid", 3);
        fourth_hidden.forward_pass("sigmoid", 4); 
        fifth_hidden.forward_pass("sigmoid", 5);
        sixth_hidden.forward_pass("sigmoid", 6);
        output_layer.forward_pass("linear", 7, true);

        //output_layer.RandomTraining(results);
        output_layer.BackPropagation(results); 
        //cout << "Final output: " << outputs[weights.size()].transpose() << endl;

    }

    cout << "Final output: " << outputs[weights.size()].transpose() << endl;
    cout << "Expected results: " << results.transpose() << endl; 

    // Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "\nElapsed time: " << elapsed_time.count() << " seconds.\n"
         << endl;

    return 0;
}
