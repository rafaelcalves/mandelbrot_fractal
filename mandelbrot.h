//
// Created by Correa, Rafael on 31/05/21.
//

#ifndef MANDELBROT_FRACTAL_MANDELBROT_H
#define MANDELBROT_FRACTAL_MANDELBROT_H

#include "color_palette.h"

class Mandelbrot {
public:
    const int ITERATION_LIMIT = 1024;
    int height, width;

    Mandelbrot(int height, int width){
        this->height=height;
        this->width=width;
    }

    unsigned long calculate(int col, int row){
        double c_real = (col - this->width / 2) * 4.0 / this->width;
        double c_imaginary = (row - this->height / 2) * 4.0 / this->width;
        int iterations = getIterations(c_real, c_imaginary);
        return colors->color_list[iterations];
    }

private:
    ColorPalette *colors = new ColorPalette(ITERATION_LIMIT);

    int getIterations(double c_real, double c_imaginary){
        double x = 0, y = 0;
        int iterations = 0;
        while (x*x+y*y < 4 && iterations < this->ITERATION_LIMIT) {
            double x_new = x*x-y*y+c_real;

            y = 2*x*y+c_imaginary;
            x = x_new;
            iterations++;
        }
        return iterations;
    }
};

#endif //MANDELBROT_FRACTAL_MANDELBROT_H
