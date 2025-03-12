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

double aux = 0;
int counter = 0;
double loss_value = 0;

VectorXd aux_vec;

#pragma GCC push_options
#pragma GCC optimize ("O0")

double MSE(variant<double, VectorXd> &x, variant<double, VectorXd> &y)
{
    if (holds_alternative<VectorXd>(x))
    {
        aux_vec = get<VectorXd>(x) - get<VectorXd>(y);
        aux = pow(aux_vec.norm(), 2);
    }
    else if (holds_alternative<double>(x))
    {
        aux = pow(get<double>(x) - get<double>(y), 2);
    }
    else
    {
        cerr << "Type not accepted: please try with VectorXd or double" << endl;
    }
    return aux;
}
double BCE(variant<double, VectorXd> &x, variant<double, VectorXd> &y)
{
    if (holds_alternative<VectorXd>(x))
    {
        aux_vec = get<VectorXd>(x) - get<VectorXd>(y);
        aux = pow(aux_vec.norm(), 2);
    }
    else if (holds_alternative<double>(x))
    {
        aux = pow(get<double>(x) - get<double>(y), 2);
    }
    else
    {
        cerr << "Type not accepted: please try with VectorXd or double" << endl;
    }
    return aux;
}
double MEE(variant<double, VectorXd> &x, variant<double, VectorXd> &y)
{
    if (holds_alternative<VectorXd>(x))
    {
        aux_vec = get<VectorXd>(x) - get<VectorXd>(y);
        aux = aux_vec.norm();
    }
    else if (holds_alternative<double>(x))
    {
        aux = pow(get<double>(x) - get<double>(y), 2);
        aux = pow(aux, 0.5);
    }
    else
    {
        cerr << "Type not accepted: please try with VectorXd or double" << endl;
    }
    return aux;
}

class Loss
{

public:
    double (*choice)(variant<double, VectorXd> &x, variant<double, VectorXd> &y);
    string path = "";

    Loss(string loss_function, string filepath) 
    {
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

    void calculate(variant<double, VectorXd> NN_outputs, variant<double, VectorXd> targets, int data_size)
    {
        loss_value += choice(NN_outputs, targets) / (double)data_size;
        counter++;

        if (counter == data_size)
        {
            ofstream outputFile(path, ios::app);

            outputFile << loss_value << endl;
            outputFile.close();
            counter = 0;
            loss_value = 0;
        }
    };
};

#pragma GCC pop_options

#endif