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


