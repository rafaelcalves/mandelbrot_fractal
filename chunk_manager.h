#ifndef MANDELBROT_FRACTAL_CHUNK_MANAGER_H
#define MANDELBROT_FRACTAL_CHUNK_MANAGER_H

#include <vector>
#include "chunk.h"
#include "constants.h"
#include "thread_queue.h"

using namespace std;

class ChunkManager{
public:
    ThreadQueue* initialChunks;
    ThreadQueue* toDrawChunks;
    int totalChunks;
    int processedChunks;
    int drewChunks;

    ChunkManager(){
        initialChunks = new ThreadQueue();
        toDrawChunks = new ThreadQueue();
        totalChunks = 0;
        drewChunks = 0;
        processedChunks = 0;
        createChunks();
    }

    void destroyChunks(){
        initialChunks->destroy();
        toDrawChunks->destroy();
    }

private:

    void createChunks() {
        for(int j = 0; j < WIDTH; j+=CHUNK_SIZE) {
            for(int i = 0; i < HEIGHT; i+=CHUNK_SIZE) {
                auto* chunk = new Chunk();
                chunk->initial = new Dot(j, i) ;
                chunk->final = new Dot(j + CHUNK_SIZE - 1, i + CHUNK_SIZE - 1);
                initialChunks->push(chunk);
                ++totalChunks;
            }
        }
    }
};

#endif //MANDELBROT_FRACTAL_CHUNK_MANAGER_H
