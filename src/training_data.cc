#include <training_data.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

TrainingData::TrainingData(string fname, unsigned num_inputs) :
    num_inputs(num_inputs)
{
    ifstream  data(fname);
    string line;
    
    while (getline(data, line)) {
        stringstream    stream(line);
        string          cell;
        vector<double>  row;
        
        while (getline(stream, cell, ',')) {
            row.push_back(stod(cell));
        }
        
        this->data.push_back(row);
    }
    
    this->num_outputs = this->data[0].size() - num_inputs;
    
    for (vector<double>& entry : this->data) {
        vector<double>::const_iterator inputs_begin = entry.begin();
        vector<double>::const_iterator inputs_end = entry.begin() + this->num_inputs;
        vector<double>::const_iterator outputs_begin = entry.begin() + this->num_inputs;
        vector<double>::const_iterator outputs_end = entry.end();
        vector<double> input_slice(inputs_begin, inputs_end);
        vector<double> output_slice(outputs_begin, outputs_end);
        this->expected.push_back(output_slice);
        this->inputs.push_back(input_slice);
    }
}

unsigned TrainingData::get_num_inputs()
{
    return this->num_inputs;
}

unsigned TrainingData::get_num_outputs()
{
    return this->num_outputs;
}

vector<vector<double>>& TrainingData::get_data()
{
    return this->data;
}

vector<vector<double> > & TrainingData::get_inputs()
{
    return this->inputs;
}

vector<double> TrainingData::get_inputs(unsigned int i)
{
    return this->inputs[i];
}

vector<vector<double>>& TrainingData::get_expected()
{
    return this->expected;
}

vector<double>& TrainingData::get_expected(unsigned int i)
{
    return this->expected[i];
}

vector<double>& TrainingData::get_row(unsigned row_num)
{
    return this->data[row_num];
}

double TrainingData::get_cell(unsigned row_num, unsigned column_num)
{
    return this->data[row_num][column_num];
}

unsigned int TrainingData::get_count()
{
    return this->data.size();
}


