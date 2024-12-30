#ifndef validation
#define validation

#include "lib.hpp"
#include "demiurge.hpp"
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

class Validation
{
public:
    void HoldOut(vector<VectorXd> &Inputs, vector<VectorXd> &resultsVector, vector<VectorXd> &val_data, vector<VectorXd> &val_res, int val_size)
    {
        vector<VectorXd> data_aux(Inputs.begin(), Inputs.begin() + val_size);
        vector<VectorXd> res_aux(resultsVector.begin(), resultsVector.begin() + val_size);

        vector<VectorXd> val_data_aux(Inputs.begin() + val_size, Inputs.end());
        vector<VectorXd> val_res_aux(resultsVector.begin() + val_size, resultsVector.end());

        Inputs = data_aux;
        resultsVector = res_aux;

        val_data = val_data_aux; 
        val_res = val_res_aux; 
    }
};

#endif