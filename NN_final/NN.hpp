#include "lib.hpp"
#include "layer.hpp"
#include "loss.hpp"
#include "demiurge.hpp"
#include "training.hpp"
#include <variant>
#include <optional>

using namespace std;
using namespace Eigen;

void InputPass(VectorXd input)
{
    units_output = weights[0] * input;
    outputs.insert(outputs.begin(), input);
    next_inputs.insert(next_inputs.begin(), units_output);
}

void HiddenPass(double depth)
{
    func_choiser(function_strings[depth - 1]);

    inputs = next_inputs[depth - 1]; //! Has to be checked;

    for (int k = 0; k < inputs.size(); k++)
    {
        inputs[k] = act_func(inputs[k]); // Making act_function act on input for each unit;
    }

    outputs.insert(outputs.begin() + depth, inputs);

    if (depth < hidden_and_out_units.size())
    {
        units_output = weights[depth] * inputs;                        // Calculating outputs vector;
        next_inputs.insert(next_inputs.begin() + depth, units_output); // Storing outputs;
    }
};

class NN
{
public:
    void train(string tr_alg, Loss tr_loss, string file_path, vector<VectorXd> Data, vector<VectorXd> Targets, double eta, double alpha, double lambda, int epochs)
    {
        for (int epoch = 0; epoch < epochs; epoch++)
        {
            for (int data_index = 0; data_index < Data.size(); data_index++)
            {
                for (int i = 0; i < hidden_and_out_units.size() + 1; i++)
                {
                    i == 0 ? InputPass(Data[data_index]) : HiddenPass(i);
                }

                if (tr_alg == "BP")
                {
                    //BackPropagation(Targets[data_index], eta, alpha, lambda);
                }
                else if (tr_alg == "Random")
                {
                    RandomTraining(Targets[data_index], eta, alpha, lambda);
                }
                else if (tr_alg == "Adam")
                {
                    Adam(Targets[data_index], eta, alpha, lambda);
                }
                else
                {
                    cerr << "Choice unavailable, please select a proper one." << endl;
                }
            }
        }
    };

    void train_and_validate(string tr_alg, Loss tr_loss, Loss val_loss, string file_path, vector<VectorXd> Tr_Data, VectorXd Tr_Targets, vector<VectorXd> Val_Data, VectorXd Val_Targets, double eta, double alpha, double lambda, double epochs)
    {
        for (int epoch = 0; epoch < epochs; epoch++)
        {
            for (int i = 0; i < hidden_and_out_units.size(); i++)
            {
                i == 0 ? InputPass(Tr_Data[epoch]) : HiddenPass(i);
                cout << epoch << endl;
            }

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

            // add validation here;
        }
    };

    void test(Loss test_loss, string file_path, vector<VectorXd> Test_data, VectorXd Test_results) {};
};