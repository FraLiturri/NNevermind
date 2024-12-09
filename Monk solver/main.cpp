#include "lib.hpp"
#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"
#include "data_reader.hpp"

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace Eigen;
using namespace std;

vector<VectorXd> TrainingData, TestData;
VectorXd TrainingResults, TestResults;

int training_accuracy = 0, test_accuracy = 0;
double FinalResult; //auxiliary double; 

int main(int argc, char *argv[]) // Add int argc, char *argv[] in parenthesis;
{
    // Counter starts;
    auto start = chrono::high_resolution_clock::now();

    //! Data vector (inputs to Input_Layer);
    FillData("Monk_data/monks-1binary.train", TrainingResults, TrainingData);
    FillData("Monk_data/monks-1binary.test", TestResults, TestData);

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
        for (int k = 0; k < TrainingData.size(); k++)
        {
            input_layer.forward_pass(TrainingData[k]);
            first_hidden.forward_pass("sigmoid", 1);
            output_layer.forward_pass("sigmoid", 2, true);

            output_layer.BackPropagation(TrainingResults[k], 0.1);

            if (n == atoi(argv[1]) - 1) //Accuracy calculator
            {
                outputs[weights.size()][0] >= 0.5 ? FinalResult = 1 : FinalResult = 0;
                FinalResult == TrainingResults[k] ? training_accuracy++ : 0;
            }
        }
    }

    //! Testing;
    for (int k = 0; k < TestData.size(); k++)
    {
        input_layer.forward_pass(TestData[k]);
        first_hidden.forward_pass("sigmoid", 1);
        output_layer.forward_pass("sigmoid", 2, true);

        outputs[weights.size()][0] >= 0.5 ? FinalResult = 1 : FinalResult = 0;
        FinalResult == TestResults[k] ? test_accuracy++ : 0;
    }

    cout << "Training accuracy: " << training_accuracy / (double)TrainingData.size() * 100 << "% (" << training_accuracy << "/" << TrainingData.size() << ")" << endl;
    cout << "Test accuracy: " << test_accuracy / (double)TestData.size() * 100 << "% (" << test_accuracy << "/" << TestData.size() << ")" << endl;

    // Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "\nElapsed time: " << elapsed_time.count() << " seconds."
         << endl;

    return 0;
}