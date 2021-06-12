#ifndef MANDELBROT_FRACTAL_PIXEL_H
#define MANDELBROT_FRACTAL_PIXEL_H

#include "dot.h"

class Pixel: public Dot {
public:
    unsigned long color;
    Pixel(int x, int y, unsigned long color) : Dot(x, y) {
        this->color = color;
    }
};

#endif //MANDELBROT_FRACTAL_PIXEL_H
