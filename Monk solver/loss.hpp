#ifndef loss
#define loss

#include "lib.hpp"
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

double mse, bce;

double MSE(double x, double y)
{
    mse = pow((x - y), 2);
    return mse;
}
double BCE(double x, double y)
{
    return bce;
}

double (*loss_func)(double, double);

class Loss
{
public:
    void Calculator(string f, double NN_outputs, double targets)
    {
        if (f == "MSE")
        {
            loss_func = MSE;
            loss_func(NN_outputs, targets);
        }
        else if (f == "BCE")
        {
            loss_func = BCE;
        }
        else
        {
            cout << "\nUnvailable choice as loss function." << endl;
        }
    };

    void writer(string filepath, VectorXd data, int index)
    {
        ofstream outFile(filepath, std::ios::app);
        if (outFile.is_open())
        {
            if (index = data.size()-1)
            {
                outFile << mse << endl;
                outFile.close(); // Chiude il file
            };
        }
        else
        {
            std::cerr << "Impossible to open file." << filepath << std::endl;
        }
    };

    void reset()
    {
        mse, bce = 0;
    };
};

#endif