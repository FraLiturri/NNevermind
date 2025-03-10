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

double aux;
int counter = 0;

VectorXd aux_vec;

double MSE(variant<double, VectorXd> x, variant<double, VectorXd> y)
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
double BCE(variant<double, VectorXd> x, variant<double, VectorXd> y)
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
double MEE(variant<double, VectorXd> x, variant<double, VectorXd> y)
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

double (*choice)(variant<double, VectorXd> x, variant<double, VectorXd> y);

class Loss
{
public:
    double loss_value;
    string choosen_loss;
    string path;

    Loss(string loss_function, string filepath)
    {
        choosen_loss = loss_function;
        path = filepath;
    };

    void calculator(variant<double, VectorXd> NN_outputs, variant<double, VectorXd> targets, int data_size)
    {
        #pragma omp critical
        if (choosen_loss == "MSE")
        {
            choice = MSE;
            loss_value += choice(NN_outputs, targets) / (double)data_size;
        }
        else if (choosen_loss == "BCE")
        {
            choice = BCE;
            loss_value += choice(NN_outputs, targets) / (double)data_size;
        }
        else if (choosen_loss == "MEE")
        {
            choice = MEE;
            loss_value += choice(NN_outputs, targets) / (double)data_size;
        }
        else
        {
            cout << "\nUnvailable choice as loss function. " << endl;
        }
        counter++;
        if (counter == data_size)
        {
            ofstream outputFile(path, ios::app);
            if (outputFile.is_open())
            {
                outputFile << loss_value << endl;
                outputFile.close();
            }
            else
            {
                cerr << "Errore: impossibile aprire il file " << path << endl;
            }
            counter = 0;
            loss_value = 0;
        }
    };
};

#endif