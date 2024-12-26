#ifndef loss
#define loss

#include "lib.hpp"
//#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"
#include "/home/calisse/eigen-3.4.0/Eigen/Dense"

using namespace std;
using namespace Eigen;

double aux = 0;
int counter = 0;

double MSE(double x, double y)
{
    aux = pow((x - y), 2);
    return aux;
}
double BCE(double x, double y)
{
    return aux;
}

double (*choice)(double, double);

class Loss
{
public:
    double loss_value;
    void calculator(string loss_function, string filepath, double NN_outputs, double targets, double data_size)
    {
        if (counter == data_size)
        {
            ofstream outFile(filepath, std::ios::app);
            if (outFile.is_open())
            {
                outFile << loss_value << endl;
                outFile.close(); // Chiude il file
            }
            else
            {
                std::cerr << "Impossible to open file. " << filepath << std::endl;
            }

            loss_value = 0;
            counter = 0;
        }

        if (loss_function == "MSE")
        {
            choice = MSE;
            loss_value += choice(NN_outputs, targets) / data_size;
        }
        else if (loss_function == "BCE")
        {
            choice = BCE;
            loss_value += choice(NN_outputs, targets) / data_size;
        }
        else
        {
            cout << "\nUnvailable choice as loss function. " << endl;
        }
        counter++;
    };
};

#endif