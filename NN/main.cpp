#include "lib.hpp"
#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"
#include "data_reader.hpp"
#include "loss.hpp"
#include "validation.hpp"

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace Eigen;
using namespace std;

vector<VectorXd> TrainingData, TestData, ValidationData, TrainingResults, TestResults, ValidationResults;

int training_accuracy = 0, test_accuracy = 0, validation_accuracy = 0;
double FinalResult; // auxiliary double;

int main(int argc, char *argv[]) // Add int argc, char *argv[] in parenthesis;
{
    //! Counter starts;
    auto start = chrono::high_resolution_clock::now();

    //? Cleaning data from previous runs;
    ofstream("NN_results/training_loss.txt", std::ios::trunc).close();
    ofstream("NN_results/val_loss.txt", std::ios::trunc).close();

    //! Demiurge blows;
    Demiurge NeuralNetwork(12, {20, 20}, 3); // Input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork;    // Pointer to NeuralNetwork for print_info, avoidable if not desired;

    //! Preparing data;
    DataReader Getter;
    Getter.VecAndVec("Data/ML-CUP24-TR.csv", TrainingData, TrainingResults);
    Getter.VecAndVec_Blind("Data/ML-CUP24-TS.csv", TestData);

    //! Splitting data for validation part;
    Validation Validator;
    Validator.HoldOut(TrainingData, TrainingResults, ValidationData, ValidationResults, 220);

    //! Printing NN general info: can be avoided if not desired;
    print_info(pointerNN);

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden, second_hidden, third_hidden, output_layer;
    Loss TrainingLoss, TestLoss, ValidationLoss;

    //! Output computing and training algorithm;
    for (int n = 0; n < atoi(argv[1]); n++)
    {
        for (int k = 0; k < TrainingData.size(); k++)
        {
            input_layer.forward_pass(TrainingData[k]);
            first_hidden.forward_pass("leaky_relu", 1);
            second_hidden.forward_pass("leaky_relu", 2);
            output_layer.forward_pass("linear", 3, true);

            output_layer.BackPropagation(TrainingResults[k], 0.00001, 0, 0);
            TrainingLoss.calculator("MEE", "NN_results/training_loss.txt", outputs[weights.size()], TrainingResults[k], TrainingResults.size());
            outputs.clear();
        };

        //! Validation;
        for (int k = 0; k < ValidationData.size(); k++)
        {
            input_layer.forward_pass(ValidationData[k]);
            first_hidden.forward_pass("leaky_relu", 1);
            second_hidden.forward_pass("leaky_relu", 2);
            output_layer.forward_pass("linear", 3, true);

            ValidationLoss.calculator("MEE", "NN_results/val_loss.txt", outputs[weights.size()], ValidationResults[k], ValidationResults.size());
            outputs.clear();
        }
    }

    cout << "Training loss is: " << TrainingLoss.last_loss << endl;
    cout << "Validation loss is: " << ValidationLoss.last_loss << endl;

    //! Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "\nElapsed time: " << elapsed_time.count() << " seconds. \n"
         << endl;

    return 0;
}