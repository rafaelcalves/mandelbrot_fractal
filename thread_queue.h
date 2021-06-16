#ifndef MANDELBROT_FRACTAL_QUEUE_H
#define MANDELBROT_FRACTAL_QUEUE_H

#include <queue>
#include "chunk.h"
#include "constants.h"

using namespace std;

class ThreadQueue {
public:
    queue<Chunk*>* threadChunks;
    pthread_mutex_t mutex;
    pthread_cond_t notEmpty;

    ThreadQueue(){
        threadChunks = new queue<Chunk*>();
        mutex = PTHREAD_MUTEX_INITIALIZER;
        notEmpty = PTHREAD_COND_INITIALIZER;
    }

    void destroy() {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&notEmpty);
    }

    void push(Chunk *chunk) {
        threadChunks->push(chunk);
        pthread_cond_signal(&notEmpty);
    }

    void pop() {
        threadChunks->pop();
    }

    Chunk* front(){
        return threadChunks->front();
    }

    bool isEmpty(){
        return threadChunks->empty();
    }
};

#endif //MANDELBROT_FRACTAL_QUEUE_H
