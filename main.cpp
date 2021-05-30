#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>

#include "x11_config.h"

Display *dis;
int screen;
Window win;
GC gc;
unsigned long black, white, red, blue;

int main() {
    X11Config x11;
    XEvent event;
    KeySym key;
    char text[255];
    while (1)
    {
        x11.handleEvents();
    }

    return 0;
}


