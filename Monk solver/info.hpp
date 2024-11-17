#include <iostream>
#include "layer.hpp"

//Setting info to print in main.cpp; 
void print_info()
{
    cout << "\nIn. units: " << in_units << endl;
    cout << "Hidden. layers: " << hidden_layers << endl;
    cout << "Hidden units: " << hidden_units.transpose() << endl;
    cout << "Out. units: " << out_units << endl;
    cout << "\n"; 
}