#ifndef MANDELBROT_FRACTAL_THREAD_HANDLER_H
#define MANDELBROT_FRACTAL_THREAD_HANDLER_H

#include "thread_queue.h"
#include "chunk.h"

class MultiThreadMandelbrotHandler {
public:
    const int THREADS_QUANTITY = 10;

    ThreadQueue* threadQueue;
    vector<Chunk*> chunks;
    vector<Chunk*> processedChunks;

    void* worker(void* chunk_ptr) {
        Chunk* chunk = (Chunk*) chunk_ptr;

        // More business logic.

        return 0;
    }
};

#endif //MANDELBROT_FRACTAL_THREAD_HANDLER_H
