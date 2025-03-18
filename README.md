
![NNeverMind image](https://github.com/user-attachments/assets/d575f505-557b-41b2-a67e-bb96a8a33fbc)

<p align="center">
  <img src ="https://img.shields.io/github/v/tag/FraLiturri/NNeverMind?label=version&sort=semver" alt="Version">
  <img src="https://github.com/FraLiturri/NNeverMind/actions/workflows/linux.yml/badge.svg?branch=Development" alt="Linux test">
  <img src="https://github.com/FraLiturri/NNeverMind/actions/workflows/macos.yml/badge.svg?branch=Development" alt="MacOs test">
  <img src="https://github.com/FraLiturri/NNeverMind/actions/workflows/windows.yml/badge.svg?branch=Development" alt="Windows test">
  <img src="https://img.shields.io/github/stars/FraLiturri/NNeverMind" alt= "Stars">
</p>

## ⬇️ Installation 
The download is available via GitHub or by typing
```
git clone https://github.com/FraLiturri/NNeverMind.git
```
in the terminal. 
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

For the best performances, compile using the flags `-fopenmp -O3`.

## 📖 Benchmark
The tests were executed on 500 samples (Hold-out, trained with BackPropagation), using an 11th-generation Intel(R) Core(TM) i7-1165G7 @ 2.80GHz. Time may vary on different devices.  
| Network size (only hiddens) | Grid size | Iterations | Time (seconds) |
| --- | --- |--- | --- |
| 20x20 | 1 | 1000 | 2.4 |
| 50x50 | 1 | 1000 | 6.4 |
| 100x100 | 1 | 1000 | 16.3 |
| 200x200 | 1 | 1000 | 26.9 |

## 🧱 Dependencies
This project uses the [Eigen library](https://eigen.tuxfamily.org/) under the [MPL 2.0 license](https://opensource.org/licenses/MPL-2.0). 
Logo created with [Logo.com](https://logo.com/). 
