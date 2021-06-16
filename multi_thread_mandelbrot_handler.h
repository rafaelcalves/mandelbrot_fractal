#ifndef MANDELBROT_FRACTAL_THREAD_HANDLER_H
#define MANDELBROT_FRACTAL_THREAD_HANDLER_H

#include "mandelbrot.h"
#include "chunk_manager.h"
#include "x11_config.h"
#include "constants.h"

class MultiThreadMandelbrotHandler {
public:
    Mandelbrot* mandelbrot;
    X11Config* x11Config;
    ChunkManager* chunkManager;

    MultiThreadMandelbrotHandler(){
        chunkManager = new ChunkManager();
        x11Config = new X11Config();
        mandelbrot = new Mandelbrot();
    }

    void handleEvents() {
        int eventResult = x11Config->handleEvents();
        switch (eventResult) {
            case 1:
                drawMandelbrotByChunks();
                break;
            case 0:
                chunkManager->destroyChunks();
                exit(0);
            default:
                break;
        }
    }

private:
    void drawMandelbrotByChunks() {
        initThreads();
    }

    void initThreads() {
        pthread_t processors[PROCESSORS_QUANTITY];
        pthread_t drawers[DRAWERS_QUANTITY];

        for (auto processor : processors) {
            pthread_create(&processor, nullptr, processChunks, this);
        }

        for (auto drawer : drawers) {
            pthread_create(&drawer, nullptr, drawChunks, this);
        }

        for (auto processor : processors) {
            pthread_join(processor, nullptr);
        }

        for (auto drawer : drawers) {
            pthread_join(drawer, nullptr);
        }
    }

    static void* processChunks(void* manager_ptr) {
        auto* manager = (MultiThreadMandelbrotHandler*) manager_ptr;

        while(!manager->chunkManager->initialChunks->isEmpty()) {

            pthread_mutex_lock(&manager->chunkManager->initialChunks->mutex);
            Chunk *chunk = manager->chunkManager->initialChunks->front();
            manager->chunkManager->initialChunks->pop();

            pthread_mutex_unlock(&manager->chunkManager->initialChunks->mutex);
            if(chunk) {
                for (int i = chunk->initial->x; i <= chunk->final->x; i++) {
                    for (int j = chunk->initial->y; j <= chunk->final->y; ++j) {
                        unsigned long pixel_color = manager->mandelbrot->calculate(i, j);
                        chunk->pixels.push_back(new Pixel(i, j, pixel_color));
                    }
                }
                manager->chunkManager->toDrawChunks->push(chunk);
                ++manager->chunkManager->processedChunks;
            }
        }
    }

    static void* drawChunks(void* manager_ptr) {
        auto* manager = (MultiThreadMandelbrotHandler*) manager_ptr;

        while(manager->chunkManager->totalChunks > manager->chunkManager->drewChunks) {

            pthread_mutex_lock(&manager->chunkManager->toDrawChunks->mutex);
            while(manager->chunkManager->toDrawChunks->isEmpty()) {
                pthread_cond_wait(&manager->chunkManager->toDrawChunks->notEmpty, &manager->chunkManager->toDrawChunks->mutex);
            }

            Chunk *chunk = manager->chunkManager->toDrawChunks->front();
            manager->chunkManager->toDrawChunks->pop();

            pthread_mutex_unlock(&manager->chunkManager->toDrawChunks->mutex);
            if(chunk) {
                for (Pixel *pixel: chunk->pixels) {
                    manager->x11Config->drawPixel(pixel->x, pixel->y, pixel->color);
                }
                ++manager->chunkManager->drewChunks;
            }
        }
    }
};

#endif //MANDELBROT_FRACTAL_THREAD_HANDLER_H
