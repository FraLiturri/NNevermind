![NNeverMind image](https://github.com/user-attachments/assets/d575f505-557b-41b2-a67e-bb96a8a33fbc)

<p align="center">
  <img src ="https://img.shields.io/github/v/tag/FraLiturri/NNeverMind?label=version&sort=semver" alt="Version">
  <img src="https://github.com/FraLiturri/NNeverMind/actions/workflows/linux.yml/badge.svg?branch=Development" alt="Linux test">
  <img src="https://img.shields.io/github/stars/FraLiturri/NNeverMind" alt= "Stars">
</p>

<h2>🏃 A quick look</h2>
<p>Many options are available for training algorithms, activation functions, and loss functions, allowing full customization of the neural network behavior.</p>

<h3>🔧 Configuration</h3>
<p>The user can specify:</p>

<p>
▷ <strong>Training algorithm</strong> by passing a string to the constructor:
</p>

<pre><code>NN NeuralNetwork("BP", stod(argv[1]), stod(argv[2]), stod(argv[3]), atoi(argv[4]));</code></pre>

<p>Available options:</p>
<ul>
  <li><code>"BP"</code> (Backpropagation)</li>
  <li><code>"Adam"</code></li>
  <li><code>"Random"</code></li>
</ul>

<p>
▷ <strong>Loss function</strong> during training:
</p>

<pre><code>Loss TrainingLoss("MSE", tr_loss_path);</code></pre>

<p>Available options:</p>
<ul>
  <li><code>"MSE"</code> (Mean Square Error)</li>
  <li><code>"MEE"</code> (Mean Euclidean Error)</li>
  <li><code>"BCE"</code> (Binary Cross-Entropy)</li>
</ul>

<p>
▷ <strong>Activation function</strong> for each layer:
<p>

<pre><code>Hidden_Layer first_hidden, second_hidden, output_layer;

first_hidden.create("relu", 1);
second_hidden.create("relu", 2);
output_layer.create("sigmoid", 3);</code></pre>

<p>Available options:</p>
<ul>
  <li><code>"relu"</code></li>
  <li><code>"sigmoid"</code></li>
  <li><code>"leaky_relu"</code></li>
  <li><code>"linear"</code></li>
  <li><code>"tanh"</code></li>
  <li><code>"threshold"</code></li>
</ul>

More info can be found in the Wiki (not now).

## ⬇️ Installation 
The download is available via GitHub or by typing
```
git clone https://github.com/FraLiturri/NNevermind.git
```
in the terminal. 
This package also requires Eigen, which can be installed from the official website [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) or by typing 
```
git clone https://gitlab.com/libeigen/eigen.git
```
as usually.

## 🚀 Starting engines
Before starting, setting up file paths is necessary: open the terminal and run
```
python copilot.py initialize
```
then type Eigen's path: `C:/User/.../your_path_to_eigen/Eigen/Dense` (remember to add `Eigen/Dense` and to use `/` to specify sub-directories).  
Then compile with 
```
g++ main.cpp -g -fopenmp -O3 -o build/main.exe
```
Parameters can be passed via the terminal 
```
./build/main.exe eta_value alpha_value lambda_value epochs
```
or using the interface (see next section). 

## 🤖 Using copilot.py
Use <code>copilot.py</code> to plot results with 
```
python copilot.py plot
```
or to open the interface 
```
python copilot.py search
```
through which the hyperparameters are passed for a grid search or a single run. When launched, the interface automatically compiles the code.

⚠️ Please, to perform the grid search use the name `main.cpp` for your source file, otherwise the script won't work. 

## 📖 Benchmark
The tests were executed on 500 samples (trained with BackPropagation), using an 11th-generation Intel(R) Core(TM) i7-1165G7 @ 2.80GHz. Time may vary on different devices.  
| Size (only hidden units) | Epochs | Time (seconds) |
| --- |--- | --- |
| 20x20 | 1k | 1.1 |
| 20x20 | 10k | 10.4 |
| 50x50 | 1k | 3.3 |
| 50x50 | 10k | 30.8 |
| 100x100 | 1k | 16.3 |
| 100x100 | 10k | 82.1 |
| 200x200 | 1k | 26.9 |
| 200x200x200 | 1k | 52.6 |

## 🔜 Coming soon
Tests on macOS and Windows and Adam optimization.

## 🧱 Dependencies
This project uses the [Eigen library](https://eigen.tuxfamily.org/) under the [MPL 2.0 license](https://opensource.org/licenses/MPL-2.0). 
Logo created with [Logo.com](https://logo.com/). 
