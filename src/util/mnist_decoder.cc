#include <util/mnist_decoder.h>

#include <iostream>
#include <fstream>

uint32_t MNISTDecoder::reverse_bytes(uint32_t x)
{
    uint32_t reversed;

    char* n1, * n2;
    n1 = (char*) &x;
    n2 = (char*) &reversed;

    *(n2 + 0) =  *(n1 + 3);
    *(n2 + 1) =  *(n1 + 2);
    *(n2 + 2) =  *(n1 + 1);
    *(n2 + 3) =  *(n1 + 0);
    
    return reversed;
}

MNISTDecoder::MNISTDecoder(MNISTType type, const string& fname) :
    file(new ifstream()),
    type(type)
{
    file->open(fname, ios::binary);
}

MNISTDecoder::~MNISTDecoder()
{
    this->file->close();
}

MNISTLabelHeader MNISTDecoder::decode_label_header()
{
    MNISTLabelHeader header;
    
    file->read(reinterpret_cast<char*>(&header.magic_number), sizeof(header.magic_number));
    header.magic_number = reverse_bytes(header.magic_number);
    file->read(reinterpret_cast<char*>(&header.num_items), sizeof(header.num_items));
    header.num_items = reverse_bytes(header.num_items);
    
    return header;
}

MNISTLabel MNISTDecoder::decode_label()
{
    MNISTLabel l;
    
    file->read(reinterpret_cast<char*>(&l), sizeof(l));
    
    return l;
}

vector<MNISTLabel> MNISTDecoder::decode_labels()
{
    MNISTLabelHeader header = decode_label_header();
    vector<MNISTLabel> labels;
    
    for (uint32_t i = 0; i < header.num_items; i++)
        labels.push_back(decode_label());
    
    return labels;
}

MNISTImgHeader MNISTDecoder::decode_img_header()
{
    MNISTImgHeader header;
    
    file->read(reinterpret_cast<char*>(&header.magic_number), sizeof(header.magic_number));
    header.magic_number = reverse_bytes(header.magic_number);
    file->read(reinterpret_cast<char*>(&header.num_items), sizeof(header.num_items));
    header.num_items = reverse_bytes(header.num_items);
    file->read(reinterpret_cast<char*>(&header.num_rows), sizeof(header.num_rows));
    header.num_rows = reverse_bytes(header.num_rows);
    file->read(reinterpret_cast<char*>(&header.num_columns), sizeof(header.num_columns));
    header.num_columns = reverse_bytes(header.num_columns);
    
    return header;
}

MNISTImg MNISTDecoder::decode_img()
{
    MNISTImg i;
    
    file->read(reinterpret_cast<char*>(&i.pixels), sizeof(i.pixels));
    
    return i;
}

vector<MNISTImg> MNISTDecoder::decode_images()
{
    MNISTImgHeader header = decode_img_header();
    vector<MNISTImg> images;
    
    for (uint32_t i = 0; i < header.num_items; i++)
        images.push_back(decode_img());
    
    return images;
}
