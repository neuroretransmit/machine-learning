#pragma once

#include "../perceptron.h"

class Layer
{
private:
    vector<Perceptron*> neurons;
    unsigned            num_neurons;
    
public:
    Layer(unsigned num_neurons, unsigned num_inputs);
    ~Layer();
    
    vector<Perceptron*> get_neurons();
    Perceptron*         get_neuron(unsigned i);
    unsigned            get_num_neurons();
};
