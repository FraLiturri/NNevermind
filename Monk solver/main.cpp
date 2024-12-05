#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace Eigen;
using namespace std;

int main()
{
    // Counter starts;
    auto start = chrono::high_resolution_clock::now();

    //! Data vector (inputs to Input_Layer);
    Vector<double, 3> data = {3.56, 4.89, 3};   // Creating data vector;
    Vector<double, 2> results = {20.39, -1.34}; // Expected results;

    std::string fileinput = "Monk_data/monks-1.train";
    std::string line; // declaring the std::string that will act as a placeholder for each line of the file
    std::ifstream myfile_in(fileinput);
    std::vector<int> Placeholder(6);
    std::vector<std::vector<int>> Inputs;
    std::vector<int> Results;

    if (myfile_in.is_open())
    {
        while (getline(myfile_in, line))
        {
            std::istringstream iss{line};
            std::vector<std::string> words // we make a vector of words rather than chars
                {
                    std::istream_iterator<std::string>(iss),
                    std::istream_iterator<std::string>()};
            Results.push_back(std::stoi(words[0]));
            for (int ss = 1; ss < words.size() - 1; ss++)
            {
                Placeholder.push_back(std::stoi(words[ss]));
            }
            Inputs.push_back(Placeholder);
            Placeholder.clear();
        }
    }

    //! Demiurge blows;
    Demiurge NeuralNetwork(3, {20, 40, 25, 30, 20, 12}, 2); // Input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork;                   // Pointer to NeuralNetwork, avoidable if not desired;

    // Printing NN general info: can be avoided if not desired;
    print_info(pointerNN);

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden;
    Hidden_Layer second_hidden;
    Hidden_Layer third_hidden;
    Hidden_Layer fourth_hidden;
    Hidden_Layer fifth_hidden;
    Hidden_Layer sixth_hidden;
    Hidden_Layer output_layer;

    //! Output computing and training algorithm;
    for (int n = 0; n < 60; n++)
    {
        input_layer.forward_pass(data);
        first_hidden.forward_pass("linear", 1);
        second_hidden.forward_pass("linear", 2);
        third_hidden.forward_pass("sigmoid", 3);
        fourth_hidden.forward_pass("sigmoid", 4);
        fifth_hidden.forward_pass("sigmoid", 5);
        sixth_hidden.forward_pass("sigmoid", 6);
        output_layer.forward_pass("threshold", 7, true);

        // output_layer.RandomTraining(results);
        output_layer.BackPropagation(results);
        // cout << "Final output: " << outputs[weights.size()].transpose() << endl;
    }

    cout << "Final output: " << outputs[weights.size()].transpose() << endl;
    cout << "Expected results: " << results.transpose() << endl;

    // Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "\nElapsed time: " << elapsed_time.count() << " seconds.\n"
         << endl;

    return 0;
}
