#include "include/headers.hpp"

using namespace Eigen;
using namespace std;

vector<VectorXd> TrainingData, TestData, ValidationData, TrainingResults, TestResults, ValidationResults;
string tr_loss_path = "results/tr_loss.txt", val_loss_path = "results/val_loss.txt", test_loss_path = "results/test_loss.txt";

int main(int argc, char *argv[])
{
     //! Counter starts;
     auto start = chrono::high_resolution_clock::now();
     unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Defining seed for different random numbers;

     //! Cleaning data from previous runs;
     ofstream(tr_loss_path, std::ios::trunc).close();
     ofstream(val_loss_path, std::ios::trunc).close();
     ofstream(test_loss_path, std::ios::trunc).close();

     //! Demiurge blows;
     Demiurge MLP(5, {30, 30}, 3, seed); // Input units - hidden_units vector - output units - seed;
     Demiurge *pointer = &MLP;           // Pointer to NeuralNetwork for print_info, avoidable if not desired;

     //! Preparing data;
     DataReader Getter;
     Getter.VecAndVec("data/test.csv", TrainingData, TrainingResults);

     //! Splitting data for validation part;
     Validation Validator;
     Validator.HoldOut(TrainingData, TrainingResults, ValidationData, ValidationResults, TestData, TestResults, 40, 50);

     //! Printing NN general info: can be avoided if not desired;
     print_info(pointer);

     //! Loss definition;
     Loss TrainingLoss("MSE", tr_loss_path), TestLoss("MSE", test_loss_path), ValidationLoss("MSE", val_loss_path);

     //! Neural network construction;
     Input_Layer input_layer;
     Hidden_Layer first_hidden, second_hidden, output_layer;

     first_hidden.create("relu", 1);
     second_hidden.create("relu", 2);
     output_layer.create("linear", 3);

     //! Training, Validation and Test;
     NN NeuralNetwork;
     NeuralNetwork.train("BackPropagation", TrainingLoss, TrainingData, TrainingResults, stod(argv[1]), stod(argv[2]), stod(argv[3]), atoi(argv[4]));

     cout << "outputs: " << outputs[weights.size()].transpose() << endl;
     cout << "expected: " << TrainingResults[39].transpose() << endl
          << endl;

     //! Counter stops and prints elapsed time;
     auto end = chrono::high_resolution_clock::now();
     chrono::duration<double> elapsed_time = end - start;
     cout << "Elapsed time: " << elapsed_time.count() << " seconds.\n"
          << endl;

     return 0;
}