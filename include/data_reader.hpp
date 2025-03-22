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

    void shuffle(string input_data, string shuffled_data, unsigned int seed)
    {
        vector<string> lines;

        // Use a mutex for thread-safety
        static mutex file_mutex;

        // Lock the mutex while reading from the file
        {
            lock_guard<mutex> lock(file_mutex);
            ifstream inputFile(input_data);

            if (!inputFile)
            {
                cerr << "Error: impossible to open file " << input_data << endl;
                return;
            }

            string line;
            while (getline(inputFile, line))
            {
                lines.push_back(line);
            }
            inputFile.close();
        }

        if (lines.empty())
        {
            cerr << "Error: file empty." << endl;
            return;
        }

        // The shuffling itself doesn't need a lock since we're working on a local copy
        mt19937 g(seed);
        std::shuffle(lines.begin(), lines.end(), g);

        // Lock the mutex again while writing to the output file
        {
            lock_guard<mutex> lock(file_mutex);
            ofstream outputFile(shuffled_data);
            if (!outputFile)
            {
                cerr << "Error: impossible to write to file " << shuffled_data << endl;
                return;
            }

            for (const auto &shuffledLine : lines)
            {
                outputFile << shuffledLine << endl;
            }
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