#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <cmath>
#include<omp.h>
#include"Utils.h"
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;

void TrueMain(HyperParameters params)
{
    std::cout
    //put here training and stuff 

}



int main(int argc char *argv[])
{
    omp_set_num_threads(32); //find a way to tune this parameter automatically...

    //genero lo spazio delle fasi ed accoppio i valori degli iperparametri agli indici.
    auto grid = generateGrid(argv[1], argv[2],argv[3],argv[4],argv[5],argv[6],argv[7]);
    std::vector<std::pair<HyperParameters, double>> HParamsAndResults(grid.size());
    auto start = chrono::high_resolution_clock::now();
    //parte con indici non randomici, itera su tutto lo spazio delle fasi

    #pragma omp parallel for //direttiva omp per parallelizzazione
    for (int k = 0; k < grid.size(); k++)
    {
        TrueMain(grid[k]);
    }

    // Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Elapsed time for sequential: " << elapsed_time.count() << " seconds.\n"
         << endl;

    //parte fatta con indici randomici, e' uguale a quella precedente se non per l'indicizzazione
    std::vector<int> RandomIndices = generateRandomIndices(grid.size(), 0.8); 
    #pragma omp parallel for //direttiva omp per parallelizzazione
    for(int k =0, k<RandomIndices.size(); k++)
    {
        TrueMain(grid(RandomIndices(k)));
    }


    return 0;
}