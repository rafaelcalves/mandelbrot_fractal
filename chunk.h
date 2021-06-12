#ifndef MANDELBROT_FRACTAL_CHUNK_H
#define MANDELBROT_FRACTAL_CHUNK_H

#include <vector>
#include "dot.h"
#include "pixel.h"
using namespace std;

class Chunk {
public:
    Dot *initial, *final;
    vector<Pixel*> pixels;
};
#endif //MANDELBROT_FRACTAL_CHUNK_H
