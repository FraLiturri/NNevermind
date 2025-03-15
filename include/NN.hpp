#include "lib.hpp"
#include "demiurge.hpp"
#include "training.hpp"
#include "loss.hpp"
#include "layer.hpp"
#include "activation_functions.hpp"

using namespace std;
using namespace Eigen;

class NN
{
private:
    int choosen_epochs = 0;
    double choosen_eta, choosen_alpha, choosen_lambda = 0;
    void (*choosen_tr_alg)(VectorXd &d, double &e, double, double);

public:
    NN(string tr_alg, double eta, double alpha, double lambda, int epochs)
    {
        choosen_epochs = epochs;
        choosen_alpha = alpha;
        choosen_eta = eta;

        if (tr_alg == "BP")
        {
            choosen_tr_alg = BackPropagation;
        }
        else if (tr_alg == "Random")
        {
            choosen_tr_alg = RandomTraining;
        }
        else if (tr_alg == "Adam")
        {
            choosen_tr_alg = Adam;
        }
        else
        {
            cerr << "Choice unavailable, please select a proper one." << endl;
        }
    };

    void train(Loss &tr_loss, vector<VectorXd> &Data, vector<VectorXd> &Targets)
    {
        for (int epoch = 0; epoch < choosen_epochs; epoch++)
        {
            adam_counter++;
            for (int data_index = 0; data_index < Data.size(); data_index++)
            {
                InputPass(Data[data_index]);
                for (int i = 1; i <= hidden_and_out_units.size(); i++)
                {
                    HiddenPass(i);
                }

                choosen_tr_alg(Targets[data_index], choosen_eta, choosen_alpha, choosen_lambda);
                tr_loss.calculate(outputs[weights.size()], Targets[data_index], Targets.size());
            }
        }
    };

    void train_and_validate(Loss &Tr_Loss, vector<VectorXd> &Tr_Data, vector<VectorXd> &Tr_Targets, Loss &Val_Loss, vector<VectorXd> &Val_Data, vector<VectorXd> &Val_Targets)
    {
        for (int epoch = 0; epoch < choosen_epochs; epoch++)
        {
            adam_counter++;
            for (int data_index = 0; data_index < Tr_Data.size(); data_index++)
            {
                InputPass(Tr_Data[data_index]);
                for (int i = 1; i <= hidden_and_out_units.size(); i++)
                {
                    HiddenPass(i);
                }

                choosen_tr_alg(Tr_Targets[data_index], choosen_eta, choosen_alpha, choosen_lambda);
                Tr_Loss.calculate(outputs[weights.size()], Tr_Targets[data_index], Tr_Targets.size());
            }

            for (int val_index = 0; val_index < Val_Data.size(); val_index++)
            {
                InputPass(Val_Data[val_index]);
                for (int i = 1; i <= hidden_and_out_units.size(); i++)
                {
                    HiddenPass(i);
                }

                Val_Loss.calculate(outputs[weights.size()], Val_Targets[val_index], Val_Targets.size());
            }
        }
    };

    void test(Loss &Test_Loss, vector<VectorXd> &Test_data, vector<VectorXd> &Test_results)
    {
        for (int test_index = 0; test_index < Test_data.size(); test_index++)
        {
            InputPass(Test_data[test_index]);
            for (int i = 1; i <= hidden_and_out_units.size(); i++)
            {
                HiddenPass(i);
            }

            Test_Loss.calculate(outputs[weights.size()], Test_results[test_index], Test_results.size());
        }
        cout << "Test loss is: " << Test_Loss.last_loss << "." << endl;
    };
};