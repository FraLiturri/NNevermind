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
    Vector<double, 2> data = {3.56, 4.89}; // Creating data vector;
    Vector<double, 1> results;
    results << 4.234;

    //! Demiurge blows;
    Demiurge NeuralNetwork(2, {1, 2}, 1); // input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork; // pointer to NeuralNetwork;

    //! Printing NN general info:
    print_info(pointerNN);

    for (int i = 0; i < 1000; i++)
    {
        //! Neural network construction;
        Input_Layer Input_Layer(data);
        Hidden_Layer First_hidden("sigmoid", 1);
        Hidden_Layer second_hidden("sigmoid", 2);
        Hidden_Layer Output_Layer("linear", 3, true);

        //! Backpropagation algorithm;
        Output_Layer.RandomTraining(results);
        cout << "Final out: " << outputs[3].transpose() << endl;
    }

    // Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Elapsed time: " << elapsed_time.count() << " seconds.\n"
         << endl;

    return 0;
}
