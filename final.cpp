#include "NN_final/lib.hpp"

using namespace Eigen;
using namespace std;

vector<VectorXd> TrainingData, TestData, ValidationData, TrainingResults, TestResults, ValidationResults;

int main(int argc, char *argv[])
{
    //! Counter starts;
    auto start = chrono::high_resolution_clock::now();

    //! Cleaning data from previous runs;
    ofstream("results/training_loss.txt", std::ios::trunc).close();
    ofstream("results/val_loss.txt", std::ios::trunc).close();
    ofstream("results/test_loss.txt", std::ios::trunc).close();

    //! Demiurge blows;
    Demiurge NeuralNetwork(12, {1, 1}, 3); // Input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork;    // Pointer to NeuralNetwork for print_info, avoidable if not desired;

    //! Preparing data;
    DataReader Getter;
    Getter.VecAndVec("data/regression.csv", TrainingData, TrainingResults);

    //! Splitting data for validation part;
    Validation Validator;
    Validator.HoldOut(TrainingData, TrainingResults, ValidationData, ValidationResults, TestData, TestResults, 180, 210);

    //! Printing NN general info: can be avoided if not desired;
    print_info(pointerNN);

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden, second_hidden, output_layer;

    Loss TrainingLoss, TestLoss, ValidationLoss;

    //!Initializing; 
    first_hidden.create("leaky_relu", 1); 
    second_hidden.create("leaky_relu", 2); 
    output_layer.create("linear", 3); 

    //! Output computing and training algorithm;
    /* for (int n = 0; n < atoi(argv[4]); n++)
    {
        for (int k = 0; k < TrainingData.size(); k++)
        {
            input_layer.forward_pass(TrainingData[k]);
            first_hidden.forward_pass("leaky_relu", 1);
            second_hidden.forward_pass("leaky_relu", 2);
            output_layer.forward_pass("linear", 3, true);

            output_layer.BackPropagation(TrainingResults[k], stod(argv[1]), stod(argv[2]), stod(argv[3]));
            TrainingLoss.calculator("MEE", "results/training_loss.txt", outputs[weights.size()], TrainingResults[k], TrainingResults.size());
            outputs.clear();
        };

        //! Validation;
        for (int k = 0; k < ValidationData.size(); k++)
        {
            input_layer.forward_pass(ValidationData[k]);
            first_hidden.forward_pass("leaky_relu", 1);
            second_hidden.forward_pass("leaky_relu", 2);
            output_layer.forward_pass("linear", 3, true);

            ValidationLoss.calculator("MEE", "results/val_loss.txt", outputs[weights.size()], ValidationResults[k], ValidationResults.size());
            outputs.clear();
        }
    }

    //! Test;
    for (int k = 0; k < TestData.size(); k++)
    {
        input_layer.forward_pass(TestData[k]);
        first_hidden.forward_pass("leaky_relu", 1);
        second_hidden.forward_pass("leaky_relu", 2);
        output_layer.forward_pass("linear", 3, true);

        ValidationLoss.calculator("MEE", "results/test_loss.txt", outputs[weights.size()], TestResults[k], TestResults.size());
        outputs.clear();
    } */

    //! Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Elapsed time: " << elapsed_time.count() << " seconds."
         << endl;

    return 0;
}