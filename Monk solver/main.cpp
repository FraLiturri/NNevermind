#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <cmath>
#include <omp.h>
#include "lib.hpp"
#include "Utils.h"
// #include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"
#include "/home/calisse/eigen-3.4.0/Eigen/Dense"

using namespace Eigen;
using namespace std;
vector<VectorXd> TrainingData, TestData;
VectorXd TrainingResults, TestResults;

int training_accuracy = 0, test_accuracy = 0;
double FinalResult; // auxiliary double;


//to test the code
double PlaceHolderMain(HyperParameters params)
{
    return 1.1;
};


// int main(int argc, char* argv[]) //

double TrueMain(HyperParameters params, int TrainingIterations) //
{
    training_accuracy = 0;
    test_accuracy = 0;
    //! Counter starts;
    
    auto start = chrono::high_resolution_clock::now();
    //! Demiurge blows;
    Demiurge NeuralNetwork(17, {4}, 1);   // Input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork; // Pointer to NeuralNetwork for print_info, avoidable if not desired;

    //! Printing NN general info: can be avoided if not desired;
    print_info(pointerNN);

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden;
    Hidden_Layer output_layer;
    Loss TrainingLoss;
    Loss TestLoss;
    //! Output computing and training algorithm;
    for (int n = 0; n < TrainingIterations /*atoi(argv[1])*/; n++)
    {
        for (int k = 0; k < TrainingData.size(); k++)
        {
            input_layer.forward_pass(TrainingData[k]);
            first_hidden.forward_pass("sigmoid", 1);
            output_layer.forward_pass("sigmoid", 2, true);
            //output_layer.BackPropagation(TrainingResults[k], params.eta, params.alpha, params.lambda);
            output_layer.BackPropagation(TrainingResults[k], 0.2, 0.001, 0.00001);

            TrainingLoss.calculator("MSE", "NN_results/training_loss.txt", outputs[weights.size()][0], TrainingResults[k], TrainingResults.size());
            if (n == TrainingIterations - 1) // Accuracy calculator;
            {
                outputs[weights.size()][0] >= 0.5 ? FinalResult = 1 : FinalResult = 0;
                FinalResult == TrainingResults[k] ? training_accuracy++ : 0;
                cout << outputs[weights.size()][0]<<" " << FinalResult << " "<< TrainingResults[k]<<endl;

            }
        }
    }

    //! Test;
    for (int k = 0; k < TestData.size(); k++)
    {
        input_layer.forward_pass(TestData[k]);
        first_hidden.forward_pass("sigmoid", 1);
        output_layer.forward_pass("sigmoid", 2, true);

        outputs[weights.size()][0] >= 0.5 ? FinalResult = 1 : FinalResult = 0;
        FinalResult == TestResults[k] ? test_accuracy++ : 0;

        TestLoss.calculator("MSE", "NN_results/test_loss.txt", outputs[weights.size()][0], TestResults[k], TestResults.size());
    }

    cout << "Training accuracy: " << training_accuracy / (double)TrainingData.size() * 100 << "% (" << training_accuracy << "/" << TrainingData.size() << ")" << endl;
    cout << "Test accuracy: " << test_accuracy / (double)TestData.size() * 100 << "% (" << test_accuracy << "/" << TestData.size() << ")" << endl;
    cout << "Test loss is: " << TestLoss.loss_value << endl;

    //! Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "\nElapsed time: " << elapsed_time.count() << " seconds."
         << endl;
    return TestLoss.loss_value;
};

int main(int argc, char *argv[])
{
    // genero lo spazio delle fasi ed accoppio i valori degli iperparametri agli indici.
    auto grid = generateGrid(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6]), std::stoi(argv[7]));

    std::vector<std::pair<HyperParameters, double>> HParamsAndResults(grid.size());
    auto start = chrono::high_resolution_clock::now();

    //! Preparing data for training and test phase;
    DataGetter("Monk_data/monks-1binary.train", TrainingResults, TrainingData);
    DataGetter("Monk_data/monks-1binary.test", TestResults, TestData);
    ofstream("NN_results/training_loss.txt", std::ios::trunc).close();
    ofstream("NN_results/test_loss.txt", std::ios::trunc).close();
    double percent = 0.8;
    // parte fatta con indici randomici, e' uguale a quella precedente se non per l'indicizzazione
    std::vector<int> RandomIndices = generateRandomIndices(grid.size(), percent);

    std::vector<std::pair<int, double>> ParamIndexAndLoss(RandomIndices.size());
    for (int k = 0; k < RandomIndices.size(); k++)
    {
        ParamIndexAndLoss[k] = (std::make_pair(RandomIndices[k], TrueMain(grid[RandomIndices[k]], std::stoi(argv[8]))));

        //! resetting variables.
        counter = 0;
        aux = 0;
        
        delta.resize(0);

        storer.clear();
        function_strings.clear();
        weights.clear();
        outputs.clear();
        next_inputs.clear();
        prev_updates.clear();
        units_output.resize(0);
        update.resize(0, 0);
        auxiliar.resize(0, 0);
        prev_weight.resize(0, 0);
        net_t.resize(0);
        delta.resize(0);
        net.resize(0);
        
    }

    std::vector<double> LossesVector(RandomIndices.size());
    std::vector<int> IndexesVector(RandomIndices.size());

    for (int k = 0; k < ParamIndexAndLoss.size(); k++)
    {
        LossesVector[k] = ParamIndexAndLoss[k].second;
        IndexesVector[k] = ParamIndexAndLoss[k].first;
    }

    int LowestLossIndex = RandomIndices[std::distance(LossesVector.begin(), std::min_element(LossesVector.begin(), LossesVector.end()))]; // indice dei parametri della griglia con la loss piu' bassa'
    HyperParameters BestParamsFromGridSearch = grid[LowestLossIndex];
    double LowestLoss = LossesVector[std::distance(LossesVector.begin(), std::min_element(LossesVector.begin(), LossesVector.end()))];
    for(auto x: LossesVector)
    {
        cout<<x<<endl;
    }
    std::cout << "La loss migliore e' :" << LowestLoss << " ed e' data dall'elemento " << LowestLossIndex << " della griglia." << std::endl;

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    std::cout << "elle" << std::endl;

    cout << "Elapsed time for sequential: " << elapsed_time.count() << " seconds." << endl;

    return 0;
}
