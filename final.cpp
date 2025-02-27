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
    Demiurge MLP(12, {200, 200}, 3); // Input units - hidden_units vector - output units;
    Demiurge *pointer = &MLP;        // Pointer to NeuralNetwork for print_info, avoidable if not desired;
    NN NeuralNetwork;

    //! Preparing data;
    DataReader Getter;
    Getter.VecAndVec("data/regression.csv", TrainingData, TrainingResults);

    //! Splitting data for validation part;
    Validation Validator;
    Validator.HoldOut(TrainingData, TrainingResults, ValidationData, ValidationResults, TestData, TestResults, 180, 210);

    //! Printing NN general info: can be avoided if not desired;
    print_info(pointer);

    //! Loss definition;
    Loss TrainingLoss, TestLoss, ValidationLoss;

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden, second_hidden, output_layer;

    first_hidden.create("leaky_relu");
    second_hidden.create("leaky_relu");
    output_layer.create("linear");

    //! Training, Validation and Test;
    NeuralNetwork.train("BP", TrainingLoss, "results/training_loss.txt", TrainingData, TrainingResults, stod(argv[1]), stod(argv[2]), stod(argv[3]), atoi(argv[4]));
    //  MLP.test();

    //! Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Elapsed time: " << elapsed_time.count() << " seconds.\n"
         << endl;

    return 0;
}