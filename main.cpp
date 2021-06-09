#include "x11_config.h"

static const int HEIGHT = 800;
static const int WIDTH = 800;

int main() {
    auto *x11 = new X11Config(HEIGHT, WIDTH);
    while (1)
    {
        x11->handleEvents();
    }
}


