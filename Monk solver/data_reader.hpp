#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include "C:/Users/franc/OneDrive/Desktop/Sync/Eigen/Eigen/Dense"

using namespace std;
using namespace Eigen;

void FillData(const string fileinput, VectorXd &resultsVector, vector<VectorXd> &Inputs)
{
    string line; // declaring the std::string that will act as a placeholder for each line of the file
    ifstream myfile_in(fileinput);
    vector<double> Placeholder(6);
    VectorXd PlaceholderConverter;
    vector<double> Results;

    if (myfile_in.is_open())
    {
        while (getline(myfile_in, line))
        {
            istringstream iss{line};
            vector<string> words // we make a vector of words rather than chars
                {
                    istream_iterator<string>(iss),
                    istream_iterator<string>()};

            Results.push_back(stoi(words[0]));
            for (int ss = 1; ss < words.size() - 1; ss++)
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


/*     std::string fileinput = "Monk_data/monks-1.train";
    std::string line; // declaring the std::string that will act as a placeholder for each line of the file
    std::ifstream myfile_in(fileinput);
    std::vector<int> Placeholder(6);
    std::vector<std::vector<int>> Inputs;
    std::vector<int> Results;

    if (myfile_in.is_open())
    {
        while (getline(myfile_in, line))
        {
            std::istringstream iss{line};
            std::vector<std::string> words // we make a vector of words rather than chars
                {
                    std::istream_iterator<std::string>(iss),
                    std::istream_iterator<std::string>()};
            Results.push_back(std::stoi(words[0]));
            for (int ss = 1; ss < words.size() - 1; ss++)
            {
                Placeholder.push_back(std::stoi(words[ss]));
            }
            Inputs.push_back(Placeholder);
            Placeholder.clear();
        }
    } */