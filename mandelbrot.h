#ifndef MANDELBROT_FRACTAL_MANDELBROT_H
#define MANDELBROT_FRACTAL_MANDELBROT_H

#include "color_palette.h"
#include "constants.h"

class Mandelbrot {
public:
    Mandelbrot(){
        colors = new ColorPalette();
    }

    unsigned long calculate(int col, int row){
        double c_real = (col - WIDTH / 2) * 4.0 / WIDTH;
        double c_imaginary = (row - HEIGHT / 2) * 4.0 / WIDTH;
        int iterations = getIterations(c_real, c_imaginary);
        unsigned long color = iterations < colors->color_list.size() ? colors->color_list.at(iterations) : 0;
        return color;
    }

private:
    ColorPalette* colors;

    static int getIterations(double c_real, double c_imaginary){
        double x = 0, y = 0;
        int iterations = 0;
        while (x*x+y*y < 4 && iterations < ITERATION_LIMIT) {
            double x_new = x*x-y*y+c_real;

            y = 2*x*y+c_imaginary;
            x = x_new;
            iterations++;
        }
        return iterations;
    }
};

#endif //MANDELBROT_FRACTAL_MANDELBROT_H
