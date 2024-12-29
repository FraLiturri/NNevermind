#ifndef data_reader
#define data_reader

#include "lib.hpp"
#include "demiurge.hpp"
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

void DataGetter(const string fileinput, VectorXd &resultsVector, vector<VectorXd> &Inputs) //, double splitting_index = 124)
{
    string line; // declaring the std::string that will act as a placeholder for each line of the file;
    ifstream myfile_in(fileinput);
    vector<double> Placeholder, Results;
    VectorXd PlaceholderConverter;

    if (myfile_in.is_open())
    {
        while (getline(myfile_in, line))
        {
            istringstream iss{line};
            vector<string> words // we make a vector of words rather than chars;
                {
                    istream_iterator<string>(iss),
                    istream_iterator<string>()};

            Results.push_back(stoi(words[0]));

            for (int ss = 1; ss < words.size(); ss++)
            {
                Placeholder.push_back(stoi(words[ss]));
            }
            PlaceholderConverter = Map<VectorXd>(Placeholder.data(), Placeholder.size());
            Inputs.push_back(PlaceholderConverter);
            Placeholder.clear();
        }
    }

    resultsVector.resize(Results.size());
    for (size_t i = 0; i < Results.size(); ++i)
    {
        resultsVector[i] = Results[i];
    }
}

void Vec2Vec(const string fileinput, vector<VectorXd> &Inputs, vector<VectorXd> &resultsVector)
{
    string line; // declaring the std::string that will act as a placeholder for each line of the file;
    ifstream myfile_in(fileinput);
    vector<double> Placeholder, SecondHolder;
    VectorXd PlaceholderConverter, SecondHolderConverter;

    if (myfile_in.is_open())
    {
        while (getline(myfile_in, line))
        {
            istringstream iss{line};
            vector<string> words // we make a vector of words rather than chars;
                {
                    istream_iterator<string>(iss),
                    istream_iterator<string>()};

            for (int ss = 1; ss < words.size(); ss++)
            {
                if (ss <= first_units)
                {
                    Placeholder.push_back(stod(words[ss]));
                }
                else if (ss > first_units)
                {
                    SecondHolder.push_back(stod(words[ss]));
                }
            }

            PlaceholderConverter = Map<VectorXd>(Placeholder.data(), Placeholder.size());
            SecondHolderConverter = Map<VectorXd>(SecondHolder.data(), SecondHolder.size());

            Inputs.push_back(PlaceholderConverter);
            resultsVector.push_back(SecondHolderConverter);

            Placeholder.clear();
            SecondHolder.clear();
        }
    }
}

void CV_HoldOut(const string fileinput, vector<VectorXd> &Inputs, vector<VectorXd> &resultsVector)
{
    string line; // declaring the std::string that will act as a placeholder for each line of the file;
    ifstream myfile_in(fileinput);
    vector<double> Placeholder, SecondHolder, ValidationDataHolder, ValidationResultsHolder;
    VectorXd PlaceholderConverter, SecondHolderConverter, ValFirstHolder, ValSecondHolder;

    if (myfile_in.is_open())
    {
        while (getline(myfile_in, line))
        {
            istringstream iss{line};
            vector<string> words // we make a vector of words rather than chars;
                {
                    istream_iterator<string>(iss),
                    istream_iterator<string>()};

            for (int ss = 1; ss < words.size(); ss++)
            {
                if (ss <= first_units)
                {
                    Placeholder.push_back(stod(words[ss]));
                }
                else if (ss > first_units)
                {
                    SecondHolder.push_back(stod(words[ss]));
                }
            }

            PlaceholderConverter = Map<VectorXd>(Placeholder.data(), Placeholder.size());
            SecondHolderConverter = Map<VectorXd>(SecondHolder.data(), SecondHolder.size());

            Inputs.push_back(PlaceholderConverter);
            resultsVector.push_back(SecondHolderConverter);

            Placeholder.clear();
            SecondHolder.clear();
        }
    }
}

void HoldOut(vector<VectorXd> &Inputs, vector<VectorXd> &resultsVector, vector<VectorXd> &val_data, vector<VectorXd> &val_res, int val_size)
{
    vector<VectorXd> aux(val_data.begin(), val_data.begin() + 2);
    for (int k = 0; k < aux.size(); k++)
    {
        cout << aux[k] << endl;
    }
}

#endif