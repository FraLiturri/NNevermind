<h1 align="center"> NNeverMind
</h1>


## ⏩ A quick look
This package offers an easy-to-use MLP with many different training choices such as: 
- Backpropagation
- Random Training
- Adam

The available choices between activation and loss functions are various (see the next sections). It's also provided a Python script for getting general info, 
data plotting, mean calculator, and a user-friendly interface for parallelized grid search. 

## ⚙️ Platforms
The entire package works perfectly in any OS, with the exception made for parallelized grid search, available for now only on: 
- Linux Mint
- Windows
  
we do not guarantee its working on other platforms.

## 📖 Benchmark

## ⬇️ Installation 
The download is available via GitHub or by typing
```
git clone https://github.com/FraLiturri/NNeverMind.git
```
in the terminal, in the desired directory. 
This package also requires Eigen, which can be installed from the official website [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) or by typing 
```
git clone https://gitlab.com/libeigen/eigen.git
```
as usually.


## 🚀 Starting engines
Before starting to build your NN, it's necessary to set up file paths. Open the terminal and run
```
python Copilot.py initialize
```
then type Eigen's path, your main path (if not specified, Python will search in NNeverMind's directory) and lastly the destination directory for training and general results.  

## 🛠️ Objects
Here there's a list of useful objects.  

| Object type | Implementation | Parameters |
| --- | --- |--- |
| `Demiurge` |  `Demiurge NeuralNetwork(int input_units, vector<int> hidden_units, int output_units)` | <ul><li>`input_units`: number of nodes in the first layer </li><li> `hidden_units` defines the number of nodes in each hidden. </li><li>`outputs_units` number of nodes in the last layer.</li></ul> |
| `Input_Layer` | `Input_Layer input_layer;` <br /> `input_layer.forward_pass(VectorXd input)` | <ul><li>`input`: the feeding data to the NN.</li></ul> |
| `Hidden_Layer.forward_pass()` | `Hidden_Layer first_hidden;` <be /> `Hidden_Layer.forward_pass(string choosen_function, int depth, bool isOutputLayer = false)` | <ul><li>`choosen_function` sets layer's activation function. Available choices: `linear`, `relu`, `leaky_relu`, `sigmoid` and `tangent`. </li><li> `Depth` is the layer number, for the last one `isOutputLayer` has to be `true` (`false` by default). </li></ul>|
| `Hidden_Layer.Backpropagation()` |  `Hidden_Layer output_layer;` <be />`output_layer.Backpropagation(variant<double, VectorXd> targets_results, eta, alpha = 0, lambda = 0)` | <ul><li>`target_results`: target values; </li><li> `eta`: learning rate;  `alpha`: for Nesterov momentum (0 by default); </li><li> `lambda`: for L2 regularization. </li></ul>|
| `Loss` | `Loss TrainingLoss;` <br />  `TrainingLoss.calculator(string loss_function, string file_path, variant<double, VectorXd> target_values, data_size` | <ul><li> `loss_function`: `MEE` (mean euclidean error), `MSE` (mean square error) and `BCE` (binary cross entropy); </li><li> `file_path`: desired path where loss results have to be stored; </li><li> `target_values`: these are the targets values to be reached by the NN; can be double (typically for classifications tasks) or VectorXd. </li><li> `data_size`: size of the data used. </li></ul>  |

## 📑 Additional info 
<details>
  <summary> Implementation example </summary><br />
  
```ruby
using namespace Eigen;
using namespace std;

vector<VectorXd> TrainingData, TestData, ValidationData, TrainingResults, TestResults, ValidationResults;

int main(int argc, char *argv[])
{
    //! Counter starts;
    auto start = chrono::high_resolution_clock::now();

    //? Cleaning data from previous runs;
    ofstream("NN_results/training_loss.txt", std::ios::trunc).close();
    ofstream("NN_results/val_loss.txt", std::ios::trunc).close();
    ofstream("NN_results/test_loss.txt", std::ios::trunc).close();

    //! Demiurge blows;
    Demiurge NeuralNetwork(12, {20, 20}, 3); // Input units - hidden_units vector - output units;
    Demiurge *pointerNN = &NeuralNetwork;    // Pointer to NeuralNetwork for print_info, avoidable if not desired;

    //! Preparing data;
    DataReader Getter;
    Getter.VecAndVec("Data/ML-CUP24-TR.csv", TrainingData, TrainingResults);
    Getter.VecAndVec_Blind("Data/ML-CUP24-TS.csv", TestData);

    //! Splitting data for validation part;
    Validation Validator;
    Validator.HoldOut(TrainingData, TrainingResults, ValidationData, ValidationResults, TestData, TestResults, 180, 210);

    //! Printing NN general info: can be avoided if not desired;
    print_info(pointerNN);

    //! Neural network construction;
    Input_Layer input_layer;
    Hidden_Layer first_hidden, second_hidden, output_layer;

    Loss TrainingLoss, TestLoss, ValidationLoss;

    //! Output computing and training algorithm;
    for (int n = 0; n < atoi(argv[1]); n++)
    {
        for (int k = 0; k < TrainingData.size(); k++)
        {
            input_layer.forward_pass(TrainingData[k]);
            first_hidden.forward_pass("leaky_relu", 1);
            second_hidden.forward_pass("leaky_relu", 2);
            output_layer.forward_pass("linear", 3, true);

            output_layer.BackPropagation(TrainingResults[k], 0.0001);
            TrainingLoss.calculator("MEE", "NN_results/training_loss.txt", outputs[weights.size()], TrainingResults[k], TrainingResults.size());
            outputs.clear();
        };

        //! Validation;
        for (int k = 0; k < ValidationData.size(); k++)
        {
            input_layer.forward_pass(ValidationData[k]);
            first_hidden.forward_pass("leaky_relu", 1);
            second_hidden.forward_pass("leaky_relu", 2);
            output_layer.forward_pass("linear", 3, true);

            ValidationLoss.calculator("MEE", "NN_results/val_loss.txt", outputs[weights.size()], ValidationResults[k], ValidationResults.size());
            outputs.clear();
        }
    }

    //! Test;
    for (int k = 0; k < TestData.size(); k++)
    {
        input_layer.forward_pass(TestData[k]);
        first_hidden.forward_pass("leaky_relu", 1);
        second_hidden.forward_pass("leaky_relu", 2);
        output_layer.forward_pass("linear", 3, true);

        ValidationLoss.calculator("MEE", "NN_results/test_loss.txt", outputs[weights.size()], TestResults[k], TestResults.size());
        outputs.clear();
    }

    //! Counter stops and prints elapsed time;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end - start;
    cout << "Elapsed time: " << elapsed_time.count() << " seconds. \n"
         << endl;

    return 0;
}
```
</details>






