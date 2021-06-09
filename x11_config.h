#ifndef MANDELBROT_FRACTAL_X11_CONFIG_H
#define MANDELBROT_FRACTAL_X11_CONFIG_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <cstdlib>

#include "mandelbrot.h"

class X11Config {
public:
    Display *display;
    int height, width;
    Window window;
    GC gc;
    int screen;
    unsigned long black, white;

    X11Config(int height, int width){
        this->height = height;
        this->width = width;
        init();
    }

    void close() const {
        XFreeGC(display, gc);
        XDestroyWindow(display, window);
        XCloseDisplay(display);
        exit(0);
    }
    void draw() {
        XClearWindow(display, window);
        drawMandelbrot();
    }

    void handleEvents() {
        XEvent event;
        KeySym key;
        char buffer[128];

        XNextEvent(display, &event);

        if(event.type==Expose && event.xexpose.count==0) {
            draw();
        }
        if(event.type==KeyPress && XLookupString(&event.xkey, buffer, 255, &key,0)==1) {
            if(key == XK_Escape || buffer[0]=='q') {
                close();
            }
            printf("You pressed the %c key!\n",buffer[0]);
        }
    }

    void drawMandelbrot(){
        auto *mandelbrot = new Mandelbrot(height,width);

        for (int row = 0; row < this->height; row++) {
            for (int col = 0; col < this->width; col++) {
                unsigned long pixel_color = mandelbrot->calculate(col, row);
                drawPixel(row,col,pixel_color);
            }
        }
    }

private:
    void drawPixel(int x, int y, unsigned long color) const
    {
        XSetForeground(display, gc, color);
        XDrawPoint(display, window, gc, x, y);
    }

    void init() {
        display=XOpenDisplay((char *)0);
        screen= DefaultScreen(display);
        white = WhitePixel(display, screen);
        black = BlackPixel(display,screen);
        window=XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, width, height, 5, white, black);
        XSetStandardProperties(display, window, "Mandelbrot Fractal", "", None, NULL, 0, NULL);
        XSelectInput(display, window, ExposureMask | ButtonPressMask | KeyPressMask);
        gc=XCreateGC(display, window, 0,0);
        XSetBackground(display,gc,white);
        XClearWindow(display, window);
        XMapRaised(display, window);
    }
};

#endif //MANDELBROT_FRACTAL_X11_CONFIG_H
