#include "lib.hpp"
#include "layer.hpp"
#include "loss.hpp"
#include "demiurge.hpp"
#include "training.hpp"
#include <variant>

using namespace std;
using namespace Eigen;

void ForwardPass(double index, VectorXd input)
{
    if (index == 0)
    {
        units_output = weights[0] * input;
        outputs.insert(outputs.begin(), input);
        next_inputs.insert(next_inputs.begin(), units_output);
    };

    func_choiser(function_strings[index]);
    inputs = next_inputs[index]; //! Has to be checked;

    for (int k = 0; k < inputs.size(); k++)
    {
        inputs[k] = act_func(inputs[k]); // Making act_function act on input for each unit;
    }

    outputs.insert(outputs.begin() + index + 1, inputs);

    if (index == hidden_and_out_units.size() +1)
    {
        units_output = weights[index] * inputs;                            // Calculating outputs vector;
        next_inputs.insert(next_inputs.begin() + index + 1, units_output); // Storing outputs;
    }
};

class NN
{
public:
    void train(Demiurge NN, string tr_alg, Loss tr_loss, string file_path, vector<VectorXd> Data, vector<VectorXd> Targets, double eta, double alpha, double lambda, double epochs)
    {
        for (int epoch = 0; epoch < epochs; epoch++)
        {
            for (int i = 0; hidden_and_out_units.size() + 1; i++)
            {
                ForwardPass(i, Data[epoch]);
            }

            if (tr_alg == "BP")
            {
                BackPropagation(Targets[epoch], eta, alpha, lambda);
            }
            else if (tr_alg == "Random")
            {
                RandomTraining(Targets[epoch], eta, alpha, lambda);
            }
            else if (tr_alg == "Adam")
            {
                Adam(Targets[epoch], eta, alpha, lambda);
            }
            else
            {
                cerr << "Choice unavailable, please select a proper one." << endl;
            }
        }
    };

    void train_and_validate(Demiurge NN, string tr_alg, Loss tr_loss, Loss val_loss, string file_path, vector<VectorXd> Tr_Data, VectorXd Tr_Targets, vector<VectorXd> Val_Data, VectorXd Val_Targets, double eta, double alpha, double lambda, double epochs)
    {
        for (int epoch = 0; epoch < epochs; epoch++)
        {
            for (int i = 0; hidden_and_out_units.size() + 1; i++)
            {
                ForwardPass(i, Tr_Data[epoch]);
            }
            // Training algorithm here
            if (tr_alg == "BP")
            {
                BackPropagation(Tr_Targets, eta, alpha, lambda); 
            }
            else if (tr_alg == "Random")
            {
                RandomTraining(Tr_Targets, eta, alpha, lambda); 
            }
            else if (tr_alg == "Adam")
            {
                Adam(Tr_Targets, eta, alpha, lambda); 
            }
            else
            {
                cerr << "Choice unavailable, please select a proper one." << endl;
            }

            //add validation here; 
        }
    };

    void test(Demiurge NN, Loss test_loss, string file_path, vector<VectorXd> Test_data, VectorXd Test_results) {};
};