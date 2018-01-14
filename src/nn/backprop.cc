#include <nn/backprop.h>

#include <cmath>

#ifdef DEBUG
    #include <iostream>
#endif

#ifdef GRAPH
    #include <gnuplot-iostream.h>
#endif

BPNN::BPNN(const vector<unsigned int>& shape)
{
    for (unsigned i = 1; i < shape.size(); i++)
        this->layers.push_back(new Layer(shape[i], shape[i - 1]));
}

BPNN::~BPNN()
{
    for (Layer* layer : this->layers)
        delete layer;
}

void BPNN::train(TrainingData& data, double learning_rate, unsigned int max_iterations)
{
#ifdef GRAPH
    vector<double> errors;
    Gnuplot gp;
#endif
    
    for (unsigned i = 0; i < max_iterations; i++) {
        double sum_error = 0.0;
        
        for (unsigned j = 0; j < data.get_count(); j++) {
            vector<double> inputs = data.get_inputs(j);
            vector<double> outputs = feed_forward(inputs);
            vector<double> expected = data.get_expected(j);
            
            for (unsigned k = 0; k < expected.size(); k++)
                sum_error += pow(expected[k] - outputs[k], 2);
            
            back_propagate(expected);
            update_weights(inputs, learning_rate);
        }
#ifdef DEBUG
        cout << ">epoch=" << i + 1 << ", lrate=" << learning_rate << ", error=" << sum_error << endl;
#endif

#ifdef GRAPH
        errors.push_back(sum_error);
        gp << "plot '-' with lines title 'Sum Error'\n";
        gp.send1d(errors);
        gp.flush();
#endif
    }
}

vector<double> BPNN::feed_forward(const vector<double>& inputs)
{
    vector<double> x = inputs;
    
    for (Layer* layer : this->layers) {
        vector<double> new_inputs;
        
        for (Perceptron* neuron : layer->get_neurons())
            new_inputs.push_back(neuron->fire(x));
        
        x = new_inputs;
    }
    
    return x;
}

void BPNN::back_propagate(const vector<double>& expected)
{
    int last_layer_idx = this->layers.size() - 1;
 
    for (int i = last_layer_idx; i >= 0; i--) {
        Layer* layer = this->layers[i];
        vector<double> errors;
        
        if (i != last_layer_idx) {
            for (unsigned j = 0; j < layer->get_num_neurons(); j++) {
                double error = 0.0;
                
                for (Perceptron* neuron : this->layers[i + 1]->get_neurons())
                    error += neuron->get_weight(j) * neuron->get_delta();
                
                errors.push_back(error);
            }
        } else {
            for (unsigned j = 0; j < layer->get_num_neurons(); j++) {
                Perceptron* neuron = layer->get_neuron(j);
                errors.push_back(expected[j] - neuron->get_output());
            }
        }
        
        for (unsigned j = 0; j < layer->get_num_neurons(); j++) {
            Perceptron* neuron = layer->get_neuron(j);
            neuron->set_delta(errors[j] * neuron->derivative());
        }
    }
}

void BPNN::update_weights(const vector<double>& inputs, double learning_rate)
{
    for (unsigned i = 0; i < this->layers.size(); i++) {
        if (i != 0) {
            vector<double> inputs;
            
            for (Perceptron* neuron : this->layers[i -1]->get_neurons())
                inputs.push_back(neuron->get_output());
        }
        
        for (Perceptron* neuron : this->layers[i]->get_neurons()) {
            for (unsigned j = 0; j < inputs.size(); j++)
                neuron->adjust_weight(j, learning_rate * neuron->get_delta() * inputs[j]);
            
            unsigned bias_idx = neuron->get_num_inputs();
            neuron->adjust_weight(bias_idx, learning_rate * neuron->get_delta());
        }
    }
}

vector<double> BPNN::predict(const vector<double>& inputs)
{
    return feed_forward(inputs);
}

