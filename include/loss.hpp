#ifndef loss
#define loss

#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"
#include "data_reader.hpp"
#include "validation.hpp"
#include "demiurge.hpp"

#include "lib.hpp"

using namespace std;
using namespace Eigen;

#pragma GCC push_options
#pragma GCC optimize("O1")

double MSE(VectorXd &x, VectorXd &y)
{
    return pow((x - y).norm(), 2);
}

double BCE(VectorXd &x, VectorXd &y)
{
    return -y[0] * log(x[0]) - (1 - y[0]) * log(1 - x[0]);
}

double MEE(VectorXd &x, VectorXd &y)
{
    return (x - y).norm();
}

class Loss
{

private:
    ofstream outputFile;
    static mutex loss_mutex;

public:
    static double loss_value;
    static int counter;
    double last_loss = 0;
    double (*choice)(VectorXd &x, VectorXd &y);

    Loss(string loss_function, string filepath) : outputFile(filepath, ios::app)
    {
        lock_guard<mutex> lock(loss_mutex);
        ofstream(filepath, ios::trunc);

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

    ~Loss()
    {
        if (outputFile.is_open())
            outputFile.close();
    }

    void calculate(VectorXd &NN_outputs, VectorXd &targets, int data_size)
    {
        loss_value += choice(NN_outputs, targets) / (double)data_size;
        counter++;

        if (counter == data_size)
        {
            isnan(loss_value) ? loss_value = 1000 : loss_value;

            {
                lock_guard<mutex> lock(loss_mutex);
                outputFile << loss_value << endl;
                outputFile.flush();
            }

            last_loss = loss_value;
            counter = 0;
            loss_value = 0;
        }
    };
};

mutex Loss::loss_mutex;
double Loss::loss_value = 0;
int Loss::counter = 0;

#pragma GCC pop_options
#endif