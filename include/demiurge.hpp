#ifndef demiurge // Checks if unit isn't defined;
#define demiurge // Define unit;

#include "lib.hpp"
#include "activation_functions.hpp"
#include "eigen_path.hpp"

using namespace std;
using namespace Eigen;

vector<VectorXd> next_inputs, outputs, biases; // init;
vector<std::string> function_strings;          // init;

vector<MatrixXd> prev_updates, V_t, M_t, weights; // init;

vector<int> hidden_and_out_units; // init;
VectorXd units_output, bias; 

VectorXd delta, net_t, net, vec_aux;
MatrixXd update, auxiliar, gradient, gradient_square, sqrt_v, M_hat, V_hat;

double epsilon = 1e-8;

int first_units, last_units, adam_counter = 0;

//! Demiurge class: the Creator;
class Demiurge
{
public:
    int in_units, out_units, hidden_layers, rows, cols = 0;
    Demiurge(int input_units, vector<int> hidden_units, int output_units, unsigned seed)
    {
        srand(seed);

        in_units = input_units;
        out_units = output_units;

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

        for (int i = 0; i < hidden_layers + 2; i++) // This cycle creates weights matrices;
        {
            i == 0 ? outputs[i].resize(input_units) : outputs[i].resize(hidden_and_out_units[i - 1]);
            outputs[i].setZero();

            i == 0 ? cols = in_units : cols = hidden_and_out_units[i - 1];              // Paying attention to first layer (input);
            i == hidden_layers + 1 ? rows = out_units : rows = hidden_and_out_units[i]; // Paying attention to last layer (output);

            bias.resize(rows);
            bias.setConstant(1);

            MatrixXd weight = MatrixXd::NullaryExpr(rows, cols, []()
                                                    { return Eigen::internal::random<double>(-0.1, 0.1); });
            MatrixXd ghost = MatrixXd::NullaryExpr(rows, cols, []()
                                                   { return Eigen::internal::random<double>(0, 0); });
            MatrixXd m_aux = MatrixXd::NullaryExpr(rows, cols, []()
                                                   { return Eigen::internal::random<double>(0, 0); });
            MatrixXd v_aux = MatrixXd::NullaryExpr(rows, cols, []()
                                                   { return Eigen::internal::random<double>(0, 0); });

            if (i < hidden_layers + 1)
            {
                i == 0 ? next_inputs[i].resize(input_units) : next_inputs[i].resize(hidden_and_out_units[i - 1]);
                next_inputs[i].setConstant(0);

                weights.push_back(weight);
                prev_updates.push_back(ghost);

                V_t.push_back(v_aux);
                M_t.push_back(m_aux);

                biases.push_back(bias);
            }
        }
    };
};

#endif