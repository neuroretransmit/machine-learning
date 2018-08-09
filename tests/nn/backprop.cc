#include <gtest/gtest.h>

#include <nn/backprop.h>
#include <util/mnist_decoder.h>
#include "../util.h"

TEST(BackProp, XOR)
{
    TrainingData xor_data = TrainingData("tests/data/xor.csv", 2);
    BPNN xor_nn = BPNN({2, 3, 1});
    xor_nn.train(xor_data, 0.1, 1000);
    vector<vector<double>> xor_nn_out;
    
    for (vector<double> inputs : xor_data.get_inputs()) {
        vector<double> tmp;
        tmp.push_back(round(xor_nn.predict(inputs)[0]));
        xor_nn_out.push_back(tmp);
    }
    
    ASSERT_EQ(xor_nn_out, xor_data.get_expected());
}

TEST(BackProp, XNOR)
{
    TrainingData xnor_data = TrainingData("tests/data/xnor.csv", 2);
    BPNN xnor_nn = BPNN({2, 3, 1});
    xnor_nn.train(xnor_data, 0.1, 2000);
    vector<vector<double>> xnor_nn_out;
    
    for (vector<double> inputs : xnor_data.get_inputs()) {
        vector<double> tmp;
        tmp.push_back(round(xnor_nn.predict(inputs)[0]));
        xnor_nn_out.push_back(tmp);
    }
    
    ASSERT_EQ(xnor_nn_out, xnor_data.get_expected());
}
