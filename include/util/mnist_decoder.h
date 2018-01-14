#pragma once

#include <cstdint>
#include <iosfwd>
#include <vector>

using namespace std;

static const uint8_t MNIST_ROWS = 22;
static const uint8_t MNIST_COLUMNS = 22;

enum MNISTType {
    MNIST_LABEL,
    MNIST_IMAGE
};

struct MNISTLabelHeader {
    uint32_t magic_number;
    uint32_t num_items;
};

struct MNISTImgHeader {
    uint32_t magic_number;
    uint32_t num_items;
    uint32_t num_rows;
    uint32_t num_columns;
};

typedef uint8_t MNISTLabel;

struct MNISTImg {
    uint8_t pixels[MNIST_ROWS * MNIST_COLUMNS];
};

class MNISTDecoder
{
private:
    ifstream*   file;
    MNISTType   type;
    size_t      size;
    
    uint32_t            reverse_bytes(uint32_t x);
    MNISTLabelHeader    decode_label_header();
    MNISTLabel          decode_label();
    MNISTImgHeader      decode_img_header();
    MNISTImg            decode_img();
    
public:
    MNISTDecoder(MNISTType type, const string& fname);
    ~MNISTDecoder();
    
    vector<MNISTLabel> decode_labels();
    vector<MNISTImg> decode_images();
};
