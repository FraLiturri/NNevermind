#include "lib.hpp"
#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"
#include "data_reader.hpp"

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace Eigen;
using namespace std;

int main() // Add int argc, char *argv[] in parenthesis;
{
    // Counter starts;
    auto start = chrono::high_resolution_clock::now();
    /*
        std::vector<VectorXd> Inputs;
        VectorXd Results;
        std::string fileinput = "Monk_data/monks-1.train";

        FillData(fileinput, Results, Inputs); */

    //! Data vector (inputs to Input_Layer);
    Vector<double, 6> data = {2, 1, 1, 2, 4, 1}; // Creating data vector;
    Vector<double, 1> _results;                  // Expected results;
    _results[0] = 0;

    //! Demiurge blows;
    Demiurge NeuralNetwork(6, {2, 3}, 1); // Input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork; // Pointer to NeuralNetwork, avoidable if not desired;

    // Printing NN general info: can be avoided if not desired;
    print_info(pointerNN);

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden;
    Hidden_Layer second_hidden;
    Hidden_Layer output_layer;

    //! Output computing and training algorithm;
    for (int n = 0; n < 4000; n++)
    {
        input_layer.forward_pass(data);
        first_hidden.forward_pass("sigmoid", 1);
        second_hidden.forward_pass("sigmoid", 2);
        output_layer.forward_pass("sigmoid", 3, true);

        // output_layer.RandomTraining(results);
        output_layer.BackPropagation(_results);
        // cout << "Final output: " << outputs[weights.size()].transpose() << endl;
    }

    cout << "\033[38;5;214mFinal output: \033[0m " << outputs[weights.size()].transpose() << endl;
    // cout << "Expected results: " << _results.transpose() << endl;

    // Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "\nElapsed time: " << elapsed_time.count() << " seconds.\n"
         << endl;

    return 0;
}
