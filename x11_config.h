//
// Created by Correa, Rafael on 30/05/21.
//

#ifndef MANDELBROT_FRACTAL_X11_CONFIG_H
#define MANDELBROT_FRACTAL_X11_CONFIG_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "dot.h"

class X11Config {
public:
    Display *display;
    int screen;
    Window window;
    GC gc;
    unsigned long black, white, red, blue;
    Dot* dot;

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
    }
    unsigned long RGB(int r, int g, int b) {
        return b + (g<<8) + (r<<16);
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
        for(;;) {
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
    }

private:
    void init() {
        dot=new Dot(100,100);
        display=XOpenDisplay((char *)0);
        screen=DefaultScreen(display);
        black=BlackPixel(display, screen);
        white=WhitePixel(display, screen);
        red=RGB(255,0,0);
        blue=RGB(0,0,255);
        window=XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 300, 300, 5, white, black);
        XSetStandardProperties(display, window, "Howdy", "Hi", None, NULL, 0, NULL);
        XSelectInput(display, window, ExposureMask | ButtonPressMask | KeyPressMask);
        gc=XCreateGC(display, window, 0,0);
        XSetBackground(display,gc,white);
        XSetForeground(display,gc,black);
        XClearWindow(display, window);
        XMapRaised(display, window);
    }
};

#endif //MANDELBROT_FRACTAL_X11_CONFIG_H
