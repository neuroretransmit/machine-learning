#pragma once

#include <vector>

#include "training_data.h"

using namespace std;

class Perceptron
{
private:
    unsigned        num_inputs;
    vector<double>  weights;
    double          output;
    double          delta;
    
public:
    
    Perceptron(unsigned num_inputs);
    
    void            train(TrainingData& data, double learning_rate, unsigned max_iterations);
    double          train(vector<double>& entry, double learning_rate);    // Returns local error
    double          fire(vector<double>& input);
    double          derivative();
    double          get_output();
    vector<double>& get_weights();
    double          get_weight(unsigned i);
    unsigned        get_num_inputs();
    void            set_weight(unsigned i, double weight);
    void            adjust_weight(unsigned i, double pe);
    double          get_delta();
    void            set_delta(double delta);
};
