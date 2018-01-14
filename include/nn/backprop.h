#pragma once

#include "layer.h"

class BPNN
{
private:
    vector<Layer*>  layers;
    
    vector<double>  feed_forward(const vector<double>& inputs);
    void            back_propagate(const vector<double>& expected);
    void            update_weights(const vector<double>& inputs, double learning_rate);
    
public:
    BPNN(const vector<unsigned>& shape);
    ~BPNN();
    
    void            train(TrainingData& data, double learning_rate, unsigned max_iterations);
    vector<double>  predict(const vector<double>& inputs);
};
