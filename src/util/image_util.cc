#include <util/image_util.h>

#include <iostream>
#include <png++/image.hpp>
#include <png++/rgb_pixel.hpp>

vector<vector<vector<double> > > decode_rgb_png(const string& fname)
{
    vector<vector<vector<double>>> rgb_image;
    
    png::image<png::basic_rgb_pixel<unsigned char>> img(fname);
    
    for (unsigned i = 0; i < img.get_width(); i++) {
        vector<vector<double>> w;
        for (unsigned j = 0; j < img.get_height(); j++) {
            vector<double> tmp;
            tmp.push_back(img[j][i].red);
            tmp.push_back(img[j][i].green);
            tmp.push_back(img[j][i].blue);
            w.push_back(tmp);
        }
        rgb_image.push_back(w);
    }
    
    return rgb_image;
}
