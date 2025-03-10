#ifndef demiurge // Checks if unit isn't defined;
#define demiurge // Define unit;

#include "lib.hpp"
#include "activation_functions.hpp"
#include "eigen_path.hpp"

using namespace std;
using namespace Eigen;

vector<MatrixXd> weights; // i-th component is the weights matrix of i-th and i+1-th layer; //? well init;
vector<VectorXd> outputs; // i-th component is the output (with weights) of i-the layer; //? well init;

vector<VectorXd> next_inputs;         //? well init;
vector<std::string> function_strings; //? well init;

vector<MatrixXd> prev_updates; // necessary for training: Nesterov; //? well init;
vector<MatrixXd> V_t, M_t;     // neceessary for Adam training; //? well init;

vector<int> hidden_and_out_units, counters; //? well init;
VectorXd units_output;                      // auxiliar vector; //? don't care init;

int first_units, last_units = 0;

//! Demiurge class: the Creator;
class Demiurge
{
public:
    int in_units, out_units, hidden_layers, rows, cols = 0;
    Demiurge(int input_units, vector<int> hidden_units, int output_units, unsigned seed)
    {
        srand(seed);

        in_units = input_units;   // correct;
        out_units = output_units; // correct;

        first_units = input_units;
        last_units = output_units;
        hidden_layers = hidden_units.size();

        //! Reserving space for vectors: no initialization;
        weights.reserve(hidden_layers);
        M_t.reserve(hidden_layers);
        V_t.reserve(hidden_layers);
        prev_updates.reserve(hidden_layers);
        hidden_units.reserve(hidden_layers + 1);

        //! Resizing vectors;
        function_strings.resize(hidden_layers + 1); // resizing collector of activation functions;
        next_inputs.resize(hidden_layers + 1);
        outputs.resize(hidden_layers + 2);

        hidden_and_out_units = hidden_units;
        hidden_and_out_units.push_back(output_units); // Adds output's units to vector;

        for (int k = 0; k < hidden_layers + 2; k++)
        {
            k == 0 ? outputs[k].resize(input_units) : outputs[k].resize(hidden_and_out_units[k - 1]);
            outputs[k].setZero();

            if (k < hidden_layers + 1)
            {
                k == 0 ? next_inputs[k].resize(input_units) : next_inputs[k].resize(hidden_and_out_units[k - 1]);
                next_inputs[k].setConstant(0);
            }
        }

        for (int i = 0; i < hidden_layers + 2; i++) // This cycle creates weights matrices;
        {
            i == 0 ? cols = in_units : cols = hidden_and_out_units[i - 1];              // Paying attention to first layer (input);
            i == hidden_layers + 1 ? rows = out_units : rows = hidden_and_out_units[i]; // Paying attention to last layer (output);

            MatrixXd weight = MatrixXd::NullaryExpr(rows, cols, []()
                                                    { return Eigen::internal::random<double>(-0.1, 0.1); });
            MatrixXd ghost = MatrixXd::NullaryExpr(rows, cols, []()
                                                   { return Eigen::internal::random<double>(0, 0); });
            MatrixXd m_aux = MatrixXd::NullaryExpr(rows, cols, []()
                                                   { return Eigen::internal::random<double>(0, 0); });
            MatrixXd v_aux = MatrixXd::NullaryExpr(rows, cols, []()
                                                   { return Eigen::internal::random<double>(0, 0); });

            if (i != hidden_layers + 1)
            {
                weights.push_back(weight);
                prev_updates.push_back(ghost);

                V_t.push_back(v_aux);
                M_t.push_back(m_aux);

                counters.push_back(0);
            }
        }
    };
};

#endif