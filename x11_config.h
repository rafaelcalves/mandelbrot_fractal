#ifndef MANDELBROT_FRACTAL_X11_CONFIG_H
#define MANDELBROT_FRACTAL_X11_CONFIG_H

static const int HEIGHT = 800;
static const int WIDTH = 800;

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <cstdlib>

#include "dot.h"
#include "coordinates.h"
#include "color_pallete.h"

class X11Config {
public:
    Display *display;
    int screen;
    Window window;
    GC gc;
    unsigned long black, white, red, blue;
    Dot* dot;
    XImage *xImage;

    X11Config(){
        init();
    }

    void close() {
        XFreeGC(display, gc);
        XDestroyWindow(display, window);
        XCloseDisplay(display);
        exit(0);
    }
    void draw() {
        XClearWindow(display, window);
        plotRandomly();
    }

    void drawLine(const XEvent &event, char *text) {
        int x=event.xbutton.x, y=event.xbutton.y;
        XSetForeground(display,gc,red);
        XDrawLine(display,window,gc,dot->x,dot->y,x,y);
        XSetForeground(display,gc,blue);
        strcpy(text,"Hello World");
        XDrawString(display,window,gc,x,y,text,strlen(text));
        dot->x=x;dot->y=y;
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
        if(event.type==ButtonPress) {
            drawLine(event, buffer);
        }
    }

    void plotImage(Coordinates *coordinate) {
        XPutImage(
            display,
            window,
            gc,
            xImage,
            coordinate->xImaginary,
            coordinate->yImaginary,
            coordinate->xImaginary,
            coordinate->yImaginary,
            (coordinate->xReal - coordinate->xImaginary + 1),
            (coordinate->yReal - coordinate->yImaginary + 1)
        );
    }

    void plotRandomly(){
        ColorPallete colors;
        for (int i = 0; i < HEIGHT * WIDTH; ++i) {
            Coordinates* coordinates = new Coordinates();
            unsigned int x = std::rand() / ((RAND_MAX + 1u) / WIDTH - 2);
            coordinates->xImaginary= x;
            coordinates->xReal= x;
            unsigned int y = std::rand() / ((RAND_MAX + 1u) / (HEIGHT -2));
            coordinates->yImaginary= y;
            coordinates->yReal= y;
            int pixelIndex = x + (y * HEIGHT);
            int color_index = std::rand() / ((RAND_MAX + 1u) / (colors.palette.size() - 1));
            ((unsigned *) xImage->data)[pixelIndex] = colors.palette[color_index];
            plotImage(coordinates);
        }
    }

private:
    void init() {
        dot=new Dot(100,100);
        display=XOpenDisplay((char *)0);
        window=XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, WIDTH, HEIGHT, 5, white, black);
        XSetStandardProperties(display, window, "Mandelbrot Fractal", "", None, NULL, 0, NULL);
        XSelectInput(display, window, ExposureMask | ButtonPressMask | KeyPressMask);
        gc=XCreateGC(display, window, 0,0);
        XSetBackground(display,gc,white);
        XSetForeground(display,gc,black);
        XClearWindow(display, window);
        XMapRaised(display, window);
        createImage();
    }

    void createImage() {
        int depth = DefaultDepth(display, DefaultScreen(display));
        Visual* visual = DefaultVisual(display, DefaultScreen(display));

        char *imageAllocation = static_cast<char *>(malloc(getImageTotalSize(depth)));
        xImage = XCreateImage(display, visual, depth, ZPixmap, 0, imageAllocation, WIDTH, HEIGHT, 32, 0);
    }
    
    int getImageTotalSize(int depth) {
        int bytesNeededForImage = 1;
        int buffer, total;
        bytesNeededForImage = 1;
        buffer = (depth - 1) >> 2;
        while (buffer >>= 1) {
            bytesNeededForImage <<= 1;
        }

        total = HEIGHT * bytesNeededForImage;
        total = (total + 3) & ~3;
        total *= WIDTH;

        return total;
    }
};

#endif //MANDELBROT_FRACTAL_X11_CONFIG_H
