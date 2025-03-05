#ifndef lib
#define lib

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <omp.h>

//!Have to be deleted: each library has to be included manually; 
#include "NN.hpp"
#include "layer.hpp"
#include "activation_functions.hpp"
#include "info.hpp"
#include "training.hpp"
#include "data_reader.hpp"
#include "loss.hpp"
#include "validation.hpp"
#include "eigen_path.hpp"

namespace Libraries
{
    using namespace std;
}

#endif