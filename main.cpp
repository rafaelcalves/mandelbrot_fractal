#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>

#include "x11_config.h"

int main() {
    X11Config x11;
    while (1)
    {
        x11.handleEvents();
    }
}


