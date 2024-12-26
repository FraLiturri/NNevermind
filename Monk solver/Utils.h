#include<vector>
#include<tuple>
#include<iostream>
#include <random>
#include<algorithm>


struct HyperParameters
{
    double eta;
    double lambda;
    double alpha;
};



std::vector<HyperParameters> generateGrid(double min1, double max1, double min2, double max2, double min3, double max3, int steps)
{
    std::vector<HyperParameters>grid;

    double StepSize1 = (max1-min1)/(steps-1);
    double StepSize2 = (max2-min2)/(steps-1);
    double StepSize3 = (max3-min3)/(steps-1);

    for(int i = 0 ; i<steps; i++)
    {
        for(int j =0; j<steps; j++)
        {
            for(int k =0;k<steps;k++)
            {
                grid.push_back({
                    min1 + i*StepSize1,
                    min2 +j*StepSize2,
                    min3 +k*StepSize3
                });
            }    
        }
    }

    return grid;
};


std::vector<int> generateRandomIndices(int DataLength, double percentual)
{
    std::random_device rd;
    std::mt19937 gen(rd()); //scelgo un generatore a caso di numeri casuali
    std::vector<int> indices(DataLength);
    //creo il vettore di indici originale
    for(int j =0; j<DataLength; j++)
    {
        indices[j] = j;
    }
    //faccio uno shuffle
    std::shuffle(indices.begin(), indices.end(), gen);

    //ora per selezionare la percentuale di grid search, semplicemente prendo i primi N su grid.size numeri, dove N/M e' la percentuale.
    int N = std::round(DataLength*percentual);
    std::vector<int> RandomIndices(N);
    for(int j = 0; j<N; j++)
    {
        RandomIndices[j] = indices[j];
    }
    return RandomIndices;

}



