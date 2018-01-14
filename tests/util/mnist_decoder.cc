#include <gtest/gtest.h>

#include <util/mnist_decoder.h>

TEST(MNISTDecoder, TrainLabel)
{
    MNISTDecoder decoder = MNISTDecoder(MNIST_LABEL, "tests/data/mnist/train-labels.idx1-ubyte");
    vector<MNISTLabel> labels = decoder.decode_labels();
    ASSERT_EQ(labels.size(), 60000);
}

TEST(MNISTDecoder, TrainImg)
{
    MNISTDecoder decoder = MNISTDecoder(MNIST_IMAGE, "tests/data/mnist/train-images.idx3-ubyte");
    vector<MNISTImg> images = decoder.decode_images();
    ASSERT_EQ(images.size(), 60000);
}
