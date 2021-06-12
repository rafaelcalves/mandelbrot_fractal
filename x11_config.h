#ifndef MANDELBROT_FRACTAL_X11_CONFIG_H
#define MANDELBROT_FRACTAL_X11_CONFIG_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <cstdlib>
#include <vector>

#include "chunk.h"
#include "multi_thread_mandelbrot_handler.h"
#include "mandelbrot.h"

using namespace std;

class X11Config {
public:
    const int HEIGHT = 800;
    const int WIDTH = 800;
    const int CHUNK_SIZE = 100;

    Display *display;
    Window window;
    GC gc;
    int screen;
    unsigned long black, white;
    MultiThreadMandelbrotHandler* handler;

    X11Config(){
        init();
    }

    void handleEvents() {
        XEvent event;
        KeySym key;
        char buffer[128];

        XNextEvent(display, &event);

        if(event.type==Expose && event.xexpose.count==0) {
            draw();
        }
        if(event.type==KeyPress && XLookupString(&event.xkey, buffer, 255, &key,nullptr)==1) {
            if(key == XK_Escape || buffer[0]=='q') {
                close();
            }
            printf("You pressed the %c key!\n",buffer[0]);
        }
    }

    void drawPixel(int x, int y, unsigned long color) const
    {
        XSetForeground(display, gc, color);
        XDrawPoint(display, window, gc, x, y);
    }

private:
    void init() {
        display=XOpenDisplay((char *)nullptr);
        screen= DefaultScreen(display);
        white = WhitePixel(display, screen);
        black = BlackPixel(display,screen);
        window=XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, WIDTH, HEIGHT, 5, white, black);
        XSetStandardProperties(display, window, "Mandelbrot Fractal", "", None, nullptr, 0, nullptr);
        XSelectInput(display, window, ExposureMask | ButtonPressMask | KeyPressMask);
        gc=XCreateGC(display, window, 0,nullptr);
        XSetBackground(display,gc,white);
        XClearWindow(display, window);
        XMapRaised(display, window);

        handler = new MultiThreadMandelbrotHandler();
        createChunks();
    }

    void createChunks(){
        for(int j = 0; j < WIDTH; j+=CHUNK_SIZE) {
            for(int i = 0; i < HEIGHT; i+=CHUNK_SIZE) {
                auto* chunk = new Chunk();
                chunk->initial = new Dot(j,i) ;
                chunk->final = new Dot(j + CHUNK_SIZE - 1, i + CHUNK_SIZE - 1);

                handler->chunks.push_back(chunk);
            }
        }
    }

    void draw() {
        XClearWindow(display, window);
        drawMandelbrotByChunks();
    }

    void drawMandelbrotByChunks() {
        processChunks();
        drawChunks();
    }

    void processChunks() {
        auto *mandelbrot = new Mandelbrot(HEIGHT,WIDTH);

        for(Chunk* chunk: handler->chunks){
            for(int i = chunk->initial->x; i <= chunk->final->x; i++){
                for (int j = chunk->initial->y; j <= chunk->final->y; ++j) {
                    unsigned long pixel_color = mandelbrot->calculate(i, j);
                    chunk->pixels.push_back(new Pixel(i,j,pixel_color));
                }
            }
            handler->processedChunks.push_back(chunk);
        }
    }

    void drawChunks() {
        for(Chunk* chunk: handler->processedChunks){
            for(Pixel* pixel: chunk->pixels){
                drawPixel(pixel->x,pixel->y,pixel->color);
            }
        }
    }

    void close() const {
        XFreeGC(display, gc);
        XDestroyWindow(display, window);
        XCloseDisplay(display);
        exit(0);
    }
};

#endif //MANDELBROT_FRACTAL_X11_CONFIG_H
