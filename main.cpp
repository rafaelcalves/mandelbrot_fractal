#include "multi_thread_mandelbrot_handler.h"

int main() {
    auto* handler = new MultiThreadMandelbrotHandler();
    while (1)
    {
        handler->handleEvents();
    }
}


