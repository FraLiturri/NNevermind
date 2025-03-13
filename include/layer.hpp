#ifndef layer // Checks if unit isn't defined;
#define layer // Define unit;

#include "lib.hpp"
#include "activation_functions.hpp"
#include "demiurge.hpp"

#include <variant>

using namespace std;
using namespace Eigen;

VectorXd inputs;

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

#endif