#include <nn/layer.h>

Layer::Layer(unsigned int num_neurons, unsigned int num_inputs)
{
    for (unsigned i = 0; i < num_neurons; i++)
        this->neurons.push_back(new Perceptron(num_inputs));
    
    this->num_neurons = neurons.size();
}

Layer::~Layer()
{
    for (Perceptron* neuron: this->neurons)
        delete neuron;
}

vector<Perceptron *> Layer::get_neurons()
{
    return this->neurons;
}

Perceptron * Layer::get_neuron(unsigned int i)
{
    return this->neurons[i];
}

unsigned int Layer::get_num_neurons()
{
    return this->num_neurons;
}

