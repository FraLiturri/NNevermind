#ifndef activation_functions
#define activation_functions

#include <cmath>
#include <string>

using namespace std;

// Defining activation functions;
double sigmoid(double x)
{
    return 1;
}

double linear(double x)
{
    return x;
}

double threshold(double x)
{
    double threshold;
    x > 0 ? threshold = 1 : threshold = 0;
    return threshold;
}

// Defining pointer to activation function(s);
double (*act_func)(double); // pointer to f;

// Choosing activation function;
void func_choiser(std::string choice)
{
    if (choice == "sigmoid")
    {
        act_func = sigmoid;
    }
    else if (choice == "linear")
    {
        act_func = linear;
    }
    else if (choice == "threshold")
    {
        act_func = threshold;
    }
    else
    {
        cout << "\nChoice unavailable.\n"
             << endl;
    }
}

#endif