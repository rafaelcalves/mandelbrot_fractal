#include "x11_config.h"

int main() {
    auto *x11 = new X11Config();
    while (1)
    {
        x11->handleEvents();
    }
}


