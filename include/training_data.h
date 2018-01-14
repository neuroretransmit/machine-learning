#pragma once

#include <vector>
#include <string>

using namespace std;

class TrainingData
{
private:
    vector<vector<double>>  data;
    vector<vector<double>>  inputs;
    vector<vector<double>>  expected;
    unsigned                num_inputs;
    unsigned                num_outputs;
    
public:
    TrainingData(string fname, unsigned num_inputs);
    
    unsigned                get_num_inputs();
    unsigned                get_num_outputs();
    vector<vector<double>>& get_data();
    vector<vector<double>>& get_inputs();
    vector<double>          get_inputs(unsigned i);
    vector<vector<double>>& get_expected();
    vector<double>&         get_expected(unsigned i);
    vector<double>&         get_row(unsigned row_num);
    double                  get_cell(unsigned row_num, unsigned col_num);
    unsigned                get_count();
};
