#ifndef MANDELBROT_FRACTAL_COLOR_PALLETE_H
#define MANDELBROT_FRACTAL_COLOR_PALLETE_H

#include <vector>

class ColorPallete{
public:
    std::vector<unsigned long> palette;
    ColorPallete() {
        palette = {
            RGB(0, 0, 0),         // black
            RGB(255, 255, 255),   // white
            RGB(255, 0, 0),       // red
            RGB(0, 0, 255),       // blue
        };
    }

private:
    unsigned long RGB(int r, int g, int b) {
        return b + (g<<8) + (r<<16);
    }
};

#endif //MANDELBROT_FRACTAL_COLOR_PALLETE_H
