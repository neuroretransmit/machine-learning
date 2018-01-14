#include <perceptron.h>

#include <random>

#ifdef DEBUG
#include <iostream>
#endif

using namespace std;

/* Uniform random stuff */
static mt19937 mt(-1);
static uniform_real_distribution<double> dist(uniform_real_distribution<double>(-1, 1));

static const unsigned BIAS = 1;
static unsigned       BIAS_IDX = 0;

Perceptron::Perceptron(unsigned num_inputs) :
    num_inputs(num_inputs)
{
    for (unsigned i = 0; i < this->num_inputs + BIAS; i++)
        this->weights.push_back(dist(mt));
    
    BIAS_IDX = num_inputs;
}

void Perceptron::train(TrainingData& data, double learning_rate, unsigned max_iterations)
{
    double global_err = 0;
    unsigned iteration = 0;
    
    vector<vector<double>>& training_data = data.get_data();
    
    do {
        iteration++;

        for (unsigned i = 0; i < training_data.size(); i++) {
            double local_err = train(training_data[i], learning_rate);
            global_err += (local_err * local_err);
        }
    } while (global_err != 0 && iteration <= max_iterations);
}

double Perceptron::train(vector<double>& entry, double learning_rate)
{
    double output = fire(entry);
    double local_err = entry[this->num_inputs] - output;
            
    for (unsigned j = 0; j < num_inputs; j++)
        this->weights[j] += learning_rate * local_err * entry[j];
    
    this->weights[BIAS_IDX] += learning_rate * local_err;
    
    return local_err;
}

double Perceptron::fire(vector<double>& input)
{
    double dot_product = 0;
    
    for (unsigned i = 0; i < num_inputs; i++)
        dot_product += input[i] * weights[i];
    
    dot_product += this->weights[BIAS_IDX];
    return output = tanh(dot_product);
}

double Perceptron::derivative()
{
    return 1.0 - pow(this->output, 2);
}

double Perceptron::get_output()
{
    return this->output;
}

double Perceptron::get_weight(unsigned int i)
{
    return this->weights[i];
}

vector<double>& Perceptron::get_weights()
{
    return this->weights;
}

unsigned int Perceptron::get_num_inputs()
{
    return this->num_inputs;
}

void Perceptron::set_weight(unsigned i, double weight)
{
    this->weights[i] = weight;
}

void Perceptron::adjust_weight(unsigned int i, double pe)
{
    this->weights[i] += pe;
}

double Perceptron::get_delta()
{
    return this->delta;
}

void Perceptron::set_delta(double delta)
{
    this->delta = delta;
}
