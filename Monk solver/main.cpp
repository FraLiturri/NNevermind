#include "lib.hpp"
#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"
#include "data_reader.hpp"

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace Eigen;
using namespace std;

vector<VectorXd> Data;
VectorXd Results;

int nn = 0;
double FinalResult;

int main(int argc, char *argv[]) // Add int argc, char *argv[] in parenthesis;
{
    // Counter starts;
    auto start = chrono::high_resolution_clock::now();

    //! Data vector (inputs to Input_Layer);
    FillData("Monk_data/monks-2binary.train", Results, Data);

    //! Demiurge blows;
    Demiurge NeuralNetwork(17, {4}, 1);   // Input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork; // Pointer to NeuralNetwork for print_info, avoidable if not desired;

    // Printing NN general info: can be avoided if not desired;
    print_info(pointerNN);

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden;
    Hidden_Layer output_layer;

    //! Output computing and training algorithm;
    for (int n = 0; n < atoi(argv[1]); n++)
    {
        for (int k = 0; k < Data.size(); k++)
        {
            input_layer.forward_pass(Data[k]);
            first_hidden.forward_pass("sigmoid", 1);
            output_layer.forward_pass("sigmoid", 2, true);

            output_layer.BackPropagation(Results[k], 0.1);

            if (n == atoi(argv[1]) - 1)
            {
                outputs[weights.size()][0] >= 0.5 ? FinalResult = 1 : FinalResult = 0;
                FinalResult == Results[k] ? nn++ : 0;
            }
        }
    }

    cout << "\nAccuracy: " << nn / (double)169 << " " << nn << " " << Data.size() << endl;

    //! Testing;
    nn = 0;
    Data.clear();
    Results.setZero();

    FillData("Monk_data/monks-2binary.test", Results, Data);

    for (int k = 0; k < Data.size(); k++)
    {
        input_layer.forward_pass(Data[k]);
        first_hidden.forward_pass("sigmoid", 1);
        output_layer.forward_pass("sigmoid", 2, true);

        outputs[weights.size()][0] >= 0.5 ? FinalResult = 1 : FinalResult = 0;
        FinalResult == Results[k] ? nn++ : 0;
    }

    cout << "\nAccuracy: " << nn / (double)432 << " " << nn << " " << Data.size() << endl;

    // Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "\nElapsed time: " << elapsed_time.count() << " seconds.\n"
         << endl;

    return 0;
}