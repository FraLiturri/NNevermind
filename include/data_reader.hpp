#ifndef data_reader
#define data_reader

#include "lib.hpp"
#include "demiurge.hpp"

using namespace std;
using namespace Eigen;

class DataReader
{
public:
    void read(const string fileinput, vector<VectorXd> &Inputs, vector<VectorXd> &resultsVector)
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

    void shuffle(string input_data, string shuffled_data, unsigned int seed) {
        vector<std::string> lines;
        ifstream inputFile(input_data);
        
        if (!inputFile) {
            cerr << "Error: impossible to open file " << input_data << std::endl;
            return;
        }
    
        string line;
        while (std::getline(inputFile, line)) {
            lines.push_back(line);
        }
        inputFile.close();
    
        if (lines.empty()) {
            std::cerr << "Error: file empty." << std::endl;
            return;
        }
    
        std::mt19937 g(seed);
        std::shuffle(lines.begin(), lines.end(), g);
    
        std::ofstream outputFile(shuffled_data);
        if (!outputFile) {
            std::cerr << "Error: impossible to write to file" << shuffled_data << std::endl;
            return;
        }
    
        for (const auto& shuffledLine : lines) {
            outputFile << shuffledLine << endl;
        }
    }

    void read_noID(const string fileinput, vector<VectorXd> &Inputs, vector<VectorXd> &resultsVector)
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

    void blindfolded_reader(const string fileinput, vector<VectorXd> &Inputs)
    {
        string line; // declaring the std::string that will act as a placeholder for each line of the file;
        ifstream myfile_in(fileinput);
        vector<double> Placeholder;
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

                for (int ss = 1; ss < words.size(); ss++)
                {
                    Placeholder.push_back(stod(words[ss]));
                }

                PlaceholderConverter = Map<VectorXd>(Placeholder.data(), Placeholder.size());

                Inputs.push_back(PlaceholderConverter);

                Placeholder.clear();
            }
        }
    }
};

#endif