#include <gtest/gtest.h>

#include <perceptron.h>

#include "util.h"

TEST(Perceptron, OR)
{
    TrainingData or_data = TrainingData("tests/data/or.csv", 2);
    Perceptron p_or = Perceptron(2);
    p_or.train(or_data, 0.1, 1000);
    vector<vector<double>> p_or_out;
    
    for (vector<double> inputs : or_data.get_inputs()) {
        vector<double> tmp;
        tmp.push_back(round(p_or.fire(inputs)));
        p_or_out.push_back(tmp);
    }
    
    ASSERT_EQ(p_or_out, or_data.get_expected());
}

TEST(Perceptron, AND)
{
    TrainingData and_data = TrainingData("tests/data/and.csv", 2);
    Perceptron p_and = Perceptron(2);
    p_and.train(and_data, 0.1, 1000);
    vector<vector<double>> p_and_out;
    
    for (vector<double> inputs : and_data.get_inputs()) {
        vector<double> tmp;
        tmp.push_back(round(p_and.fire(inputs)));
        p_and_out.push_back(tmp);
    }
    
    ASSERT_EQ(p_and_out, and_data.get_expected());
}

TEST(Perceptron, NAND)
{
    TrainingData nand_data = TrainingData("tests/data/nand.csv", 2);
    Perceptron p_nand = Perceptron(2);
    p_nand.train(nand_data, 0.1, 1000);
    vector<vector<double>> p_nand_out;
    
    for (vector<double> inputs : nand_data.get_inputs()) {
        vector<double> tmp;
        tmp.push_back(round(p_nand.fire(inputs)));
        p_nand_out.push_back(tmp);
    }
    
    ASSERT_EQ(p_nand_out, nand_data.get_expected());
}

TEST(Perceptron, NOR)
{
    TrainingData nor_data = TrainingData("tests/data/nor.csv", 2);
    Perceptron p_nor = Perceptron(2);
    p_nor.train(nor_data, 0.1, 1000);
    vector<vector<double>> p_nor_out;
    
    for (vector<double> inputs : nor_data.get_inputs()) {
        vector<double> tmp;
        tmp.push_back(round(p_nor.fire(inputs)));
        p_nor_out.push_back(tmp);
    }
    
    ASSERT_EQ(p_nor_out, nor_data.get_expected());
}
