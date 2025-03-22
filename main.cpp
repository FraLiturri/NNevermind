#include "include/headers.hpp"
#include "include/lib.hpp"

using namespace Eigen;
using namespace std;

vector<VectorXd> TrainingData, TestData, ValidationData, TrainingResults, TestResults, ValidationResults;
string tr_loss_path = "results/tr_loss.txt", val_loss_path = "results/val_loss.txt", test_loss_path = "results/test_loss.txt";

int main(int argc, char *argv[])
{
     //! Counter starts;
     auto start = chrono::high_resolution_clock::now();
     unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Defining seed for different random numbers;

     //! Demiurge blows;
     Demiurge MLP(5, {200, 200}, 1, seed); // Input units - hidden_units vector - output units - seed;
     Demiurge *pointer = &MLP;             // Pointer to NeuralNetwork for print_info, avoidable if not desired;

     //! Preparing data;
     DataReader Reader;
     Reader.shuffle("data/classification_data.csv", "data/shuffled_data.csv", seed);
     Reader.read("data/classification_data.csv", TrainingData, TrainingResults);

     //! Splitting data for validation part;
     Validation Validator;
     Validator.HoldOut(TrainingData, TrainingResults, ValidationData, ValidationResults, TestData, TestResults, 400, 450);

     //! Printing NN general info: can be avoided if not desired;
     print_info(pointer);

     //! Loss definition;
     Loss TrainingLoss("MSE", tr_loss_path), TestLoss("MSE", test_loss_path), ValidationLoss("MSE", val_loss_path);

     //! Neural network construction;
     Input_Layer input_layer;
     Hidden_Layer first_hidden, second_hidden, third_hidden, output_layer;

     first_hidden.create("relu", 1);
     second_hidden.create("relu", 2);
     output_layer.create("sigmoid", 3);

     //! Training, Validation and Test;
     NN NeuralNetwork("BP", stod(argv[1]), stod(argv[2]), stod(argv[3]), atoi(argv[4]));
     NeuralNetwork.train_and_validate(TrainingLoss, TrainingData, TrainingResults, ValidationLoss, ValidationData, ValidationResults);
     // NeuralNetwork.test(TestLoss, TestData, TestResults);

     //! Counter stops: printing elapsed time;
     auto end = chrono::high_resolution_clock::now();
     chrono::duration<double> elapsed_time = end - start;
     cout << "Elapsed time: " << elapsed_time.count() << " seconds."
          << endl;

     return 0;
}