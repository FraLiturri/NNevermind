#include "NN_final/lib.hpp"

using namespace Eigen;
using namespace std;

vector<VectorXd> TrainingData, TestData, ValidationData, TrainingResults, TestResults, ValidationResults;
string tr_loss_path = "results/training_loss.txt", val_loss_path = "results/val_loss.txt", test_loss_path = "results/test_loss.txt";

int main(int argc, char *argv[])
{
    //! Counter starts;
    auto start = chrono::high_resolution_clock::now();

    //! Cleaning data from previous runs;
    ofstream(tr_loss_path, std::ios::trunc).close();
    ofstream(val_loss_path, std::ios::trunc).close();
    ofstream(test_loss_path, std::ios::trunc).close();

    //! Demiurge blows;
    Demiurge MLP(12, {20, 20}, 3); // Input units - hidden_units vector - output units;
    Demiurge *pointer = &MLP;   // Pointer to NeuralNetwork for print_info, avoidable if not desired;
    NN NeuralNetwork;

    //! Preparing data;
    DataReader Getter;
    Getter.VecAndVec("data/regression.csv", TrainingData, TrainingResults);

    //! Splitting data for validation part;
    Validation Validator;
    Validator.HoldOut(TrainingData, TrainingResults, ValidationData, ValidationResults, TestData, TestResults, 1, 2);

    //! Printing NN general info: can be avoided if not desired;
    print_info(pointer);

    //! Loss definition;
    Loss TrainingLoss, TestLoss, ValidationLoss;

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden, second_hidden, output_layer;

    first_hidden.create("sigmoid", 1);
    second_hidden.create("sigmoid", 2);
    output_layer.create("linear", 3);

    //! Training, Validation and Test;
    NeuralNetwork.train("BackPropagation", TrainingLoss, tr_loss_path, TrainingData, TrainingResults, stod(argv[1]), stod(argv[2]), stod(argv[3]), atoi(argv[4]));

    cout << outputs[3] << endl;

    //! Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Elapsed time: " << elapsed_time.count() << " seconds.\n"
         << endl;

    return 0;
}