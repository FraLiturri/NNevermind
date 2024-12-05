#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <cmath>

#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;

double f(int &x)
{
    return x * x;
}

int main()
{
    auto start = chrono::high_resolution_clock::now();

    for (int k = 0; k < 2000000; k++)
    {
        f(k);
    }

    // Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Elapsed time: " << elapsed_time.count() << " seconds.\n"
         << endl;

    return 0;
}