# NNeverMind


## A quick look
This package offers an easy-to-use MLP with many different training choices such as: 
- Backpropagation
- Random Training
- Adam

The available choices between activation and loss functions are various (see the next sections). It's also provided a Python script for getting general info, 
data plotting, mean calculator, and a user-friendly interface for parallelized grid search. 

## Platforms
The entire package works perfectly in any OS, with the exception made for parallelized grid search, available for now only on: 
- Linux Mint
- Windows
  
we do not guarantee its working on other platforms.

## Installation 
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

## Starting engines
Run....

## Objects

| Object type | Description | Implementation | 
| --- | --- | --- |
| `Demiurge` | Initializes the weights and auxiliary matrices | `Demiurge(int input_units, vector<int> hidden_units, int output_units)` |
| `Input_Layer` | Calculates the outputs and stores them in the first component of `outputs` | `Input_Layer.forward_pass(VectorXd input)` |
| `Hidden_Layer` | Calculates the outputs and stores them in the components of `outputs`; activation functions can be chosen between: `linear`, `relu`, `leaky_relu`, `sigmoid` and `tangent` | `forward_pass(string choosen_function, int depth, bool isOutputLayer = false)` |










