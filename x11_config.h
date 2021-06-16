#ifndef MANDELBROT_FRACTAL_X11_CONFIG_H
#define MANDELBROT_FRACTAL_X11_CONFIG_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <cstdlib>
#include "constants.h"

using namespace std;

class X11Config {
public:
    Display *display;
    Window window;
    GC graphicContext;
    int screen;
    unsigned long black, white;

    X11Config(){
        init();
    }

    int handleEvents() {
        XEvent event;
        KeySym key;
        char buffer[128];

        XNextEvent(display, &event);

        if(event.type==Expose && event.xexpose.count==0) {
            clearWindow();
            return 1;
        }
        if(event.type==KeyPress && XLookupString(&event.xkey, buffer, 255, &key,nullptr)==1) {
            if(key == XK_Escape || buffer[0]=='q') {
                closeDisplay();
                return 0;
            }
            printf("You pressed the %c key!\n",buffer[0]);
        }
        return -1;
    }

    void drawPixel(int x, int y, unsigned long color) const
    {
        XSetForeground(display, graphicContext, color);
        XDrawPoint(display, window, graphicContext, x, y);
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
        graphicContext=XCreateGC(display, window, 0, nullptr);
        XSetBackground(display, graphicContext, white);
        clearWindow();
        XMapRaised(display, window);
    }

    void clearWindow() {
        XClearWindow(display, window);
    }

    void closeDisplay() const {
        XFreeGC(display, graphicContext);
        XDestroyWindow(display, window);
        XCloseDisplay(display);
    }
};

#endif //MANDELBROT_FRACTAL_X11_CONFIG_H
