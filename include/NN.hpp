#include "lib.hpp"
#include "demiurge.hpp"
#include "training.hpp"
#include "loss.hpp"
#include "activation_functions.hpp"

using namespace std;
using namespace Eigen;

void InputPass(VectorXd input)
{
    units_output = weights[0] * input;
    outputs[0] = input;
    next_inputs[0] = units_output;
}

void HiddenPass(double depth)
{
    func_choiser(function_strings[depth - 1]);

    for (int k = 0; k < next_inputs[depth - 1].size(); k++)
    {
        next_inputs[depth - 1][k] = act_func(next_inputs[depth - 1][k]); // Making act_function act on input for each unit;
    }

    outputs[depth] = next_inputs[depth - 1];

    if (depth < hidden_and_out_units.size())
    {
        units_output = weights[depth] * next_inputs[depth - 1]; // Calculating outputs vector;
        next_inputs[depth] = units_output;
    }
};

class NN
{
public:
    void train(string tr_alg, Loss &tr_loss, vector<VectorXd> Data, vector<VectorXd> &Targets, double eta, double alpha, double lambda, int epochs)
    {
         for (int epoch = 0; epoch < epochs; epoch++)
        {
            for (int data_index = 0; data_index < Data.size(); data_index++)
            {
                InputPass(Data[data_index]);
                for (int i = 1; i <= hidden_and_out_units.size(); i++)
                {
                    HiddenPass(i);
                }

                if (tr_alg == "BackPropagation")
                {
                    BackPropagation(Targets[data_index], eta, alpha, lambda);
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
                tr_loss.calculator(outputs[weights.size()], Targets[data_index], Targets.size());
            }
        } 
    };

    void train_and_validate(string tr_alg, string file_path, vector<VectorXd> Tr_Data, VectorXd Tr_Targets, vector<VectorXd> Val_Data, VectorXd Val_Targets, double eta, double alpha, double lambda, double epochs) {
         for (int epoch = 0; epoch < epochs; epoch++)
        {
            for (int i = 0; i < hidden_and_out_units.size(); i++)
            {
                i == 0 ? InputPass(Tr_Data[epoch]) : HiddenPass(i);
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

   void test(string file_path, vector<VectorXd> Test_data, VectorXd Test_results) {};
};