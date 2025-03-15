#ifndef layer // Checks if unit isn't defined;
#define layer // Define unit;

#include "lib.hpp"
#include "activation_functions.hpp"
#include "demiurge.hpp"

#include <variant>

using namespace std;
using namespace Eigen;

//! Input layer class;
class Input_Layer{};

//! Creating Layer classes;
class Hidden_Layer {
public:
    void create(string act_function, int index)
    {
        func_choiser(act_function);
        function_strings[index - 1] = act_function;
    };
};

void InputPass(VectorXd input)
{
    units_output = weights[0] * input + biases[0];
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
        units_output = weights[depth] * next_inputs[depth - 1] + biases[depth]; // Calculating outputs vector;
        next_inputs[depth] = units_output;
    }
};

#endif