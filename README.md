
![NNeverMind image](https://github.com/user-attachments/assets/d575f505-557b-41b2-a67e-bb96a8a33fbc)

<p align="center">
  <img src ="https://img.shields.io/github/v/tag/FraLiturri/NNeverMind?label=version&sort=semver" alt="Version">
  <img src="https://github.com/FraLiturri/NNeverMind/actions/workflows/linux.yml/badge.svg?branch=Development" alt="Linux test">
  <img src="https://github.com/FraLiturri/NNeverMind/actions/workflows/macos.yml/badge.svg?branch=Development" alt="MacOs test">
  <img src="https://github.com/FraLiturri/NNeverMind/actions/workflows/windows.yml/badge.svg?branch=Development" alt="Windows test">
  <img src="https://img.shields.io/github/stars/FraLiturri/NNeverMind" alt= "Stars">
</p>

## ⏩ A quick look
This package offers an easy-to-use MLP with many different training choices such as: 
- Backpropagation
- Random Training
- Adam

The available choices between activation and loss functions are various (see the next sections). It's also provided a Python script for getting general info, 
data plotting, mean calculator, and a user-friendly interface for parallelized grid search. 

## ⚙️ Platforms
The entire package should work perfectly in any OS. Report an issue if any incompatibility pops up!

## 📖 Benchmark
The tests were executed on 100-byte data sets, using an 11th-generation Intel(R) Core(TM) i7-1165G7 @ 2.80GHz. Time may vary on different devices.  
| Network size | Grid size | Iterations | Time (seconds) |
| --- | --- |--- | --- |
| 1 x 10 x 1 | 1 | 100 | 1.21 |
| 1 x 10 x 1 | 1 | 1000 | 14.83 |

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
Before starting to build your NN, setting up file paths is necessary. Open the terminal and run
```
python copilot.py initialize
```
then type Eigen's path: `C:/User/.../your_path_to_eigen/Eigen/Dense` (remember to add `Eigen/Dense` and to use `/` to specify sub-directories).  

## 🧱 Dependencies
This project uses the [Eigen library](https://eigen.tuxfamily.org/) under the [MPL 2.0 license](https://opensource.org/licenses/MPL-2.0). 
Logo created with [Logo.com](https://logo.com/). 
