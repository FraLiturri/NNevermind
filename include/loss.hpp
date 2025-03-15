#ifndef loss
#define loss

#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"
#include "data_reader.hpp"
#include "validation.hpp"
#include "eigen_path.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;
using namespace Eigen;

double aux = 0, loss_value = 0;
int counter = 0;

VectorXd aux_vec;

#pragma GCC push_options
#pragma GCC optimize("O0")

double MSE(VectorXd &x, VectorXd &y)
{
    aux_vec = x - y;
    aux = pow(aux_vec.norm(), 2);

    return aux;
}

double BCE(VectorXd &x, VectorXd &y)
{
    aux = -y[0] * log(x[0]) - (1 - y[0]) * log(1 - x[0]);
    return aux;
}

double MEE(VectorXd &x, VectorXd &y)
{
    aux_vec = x - y;
    aux = aux_vec.norm();

    return aux;
}

class Loss
{

public:
    double last_loss = 0; 
    double (*choice)(VectorXd &x, VectorXd &y);
    string path = "";

    Loss(string loss_function, string filepath)
    {
        ofstream(filepath, ios::trunc).close();
        path = filepath;
        if (loss_function == "MSE")
        {
            choice = MSE;
        }
        else if (loss_function == "BCE")
        {
            choice = BCE;
        }
        else if (loss_function == "MEE")
        {
            choice = MEE;
        }
        else
        {
            throw std::logic_error("unavailable choice as loss function.");
        }
    };

    void calculate(VectorXd &NN_outputs, VectorXd &targets, int data_size)
    {
        loss_value += choice(NN_outputs, targets) / (double) data_size;
        counter++;

        if (counter == data_size)
        {
            ofstream outputFile(path, ios::app);

            outputFile << loss_value << endl;
            outputFile.close();

            counter = 0;
            last_loss = loss_value; 
            loss_value = 0;
        }
    };
};

#pragma GCC pop_options

#endif