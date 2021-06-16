#ifndef MANDELBROT_FRACTAL_COLOR_PALETTE_H
#define MANDELBROT_FRACTAL_COLOR_PALETTE_H

#include <vector>
#include "constants.h"

using namespace std;

class ColorPalette{
public:
    vector<unsigned long> color_list;
    explicit ColorPalette() {
        colors_init(ITERATION_LIMIT);
    }

private:
    std::vector<unsigned long> palette = {
            RGB(66 , 30 , 15 ), // brown 3
            RGB(25 , 7  , 26 ), // dark violet
            RGB(9  , 1  , 47 ), // darkest blue
            RGB(4  , 4  , 73 ), // blue 5
            RGB(0  , 7  , 100), // blue 4
            RGB(12 , 44 , 138), // blue 3
            RGB(24 , 82 , 177), // blue 2
            RGB(57 , 125, 209), // blue 1
            RGB(134, 181, 229), // blue 0
            RGB(211, 236, 248), // lightest blue
            RGB(241, 233, 191), // lightest yellow
            RGB(248, 201,  95), // light yellow
            RGB(255, 170,   0), // dirty yellow
            RGB(204, 128,   0), // brown 0
            RGB(153, 87 ,   0), // brown 1
            RGB(106, 52 ,   3)  // brown 2
    };

    static unsigned long RGB(int r, int g, int b) {
        return b + (g<<8) + (r<<16);
    }

    void colors_init(int length) {
        for (int i= 0; i < length - 1; i++) {
            color_list.push_back(palette.at(i % (palette.size())));
        }
    }
};

#endif //MANDELBROT_FRACTAL_COLOR_PALETTE_H
