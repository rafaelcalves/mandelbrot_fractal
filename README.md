# MULTI THREAD MANDELBROT FRACTAL [by chunks]
> This project was develop for learning reasons and has some know issues.

> It is fully writen in english for portfolio reasons.

It aims to build an application which through multiple threads draws a mandelbrot fractal piece (chunk) by piece using `xlib` to plot the result and `pthread` to handle the multithreading.
The `main.cpp` file calls the `MultiThreadMandelbrotHandler` which will orchestrates the resources based on the configurations defined at `constants.h`.
The simple flow to process the result is:
### Initialization
   Initialize all the needed resources:

   `X11Config` is responsible for setting up the screen and result drawing.

   `ChunkManager` contains two buffers (`ThreadQueue`) which will store `initialChunks` and `toDrawChunks`.

   `Mandelbrot` is the class responsible for the fractal calculation. It iterates until the defined `ITERATION_LIMIT` and gets a color from `ColorPallete` to return as result.
### Chunks creation
   A chunk is a square defined by initial and final dots defined by a processing based on `HEIGHT` and `WIHDHT` against `CHUNK_SIZE`.
### Chunks processing
   Will iterate on all created chunks and calculate mandelbrot iterations for each pixel and store it at the chunk and move to the `toDraw` buffer.
   > This is multithreaded.
### Drawing
   Will iterate on `toDraw` buffer and draw each pixel using x11.
   > This could be multithreaded, but the current implementation brakes with more than 1 thread on the drawer.

### Known Issues
- The limit chunks is already configured, configuring a window bigger than 800x800 or setting chunks smaller than 100 will cause a runtime exception.
- The `drawer` cannot be multithreaded, probably due to an error on the mutex usage.

### Build

```shell
$ cmake -B cmake-build-debug
$ cmake --build cmake-build-debug
```

### References
#### PThreads usage
- [Multithreading Using pthreads in C language (Part 1)](https://www.youtube.com/watch?v=qPhP86HIXgg)
- [Multithreading in C Using Pthreads (part 2) - Order Violation Bugs](https://www.youtube.com/watch?v=zw8cNzX5ICc)
- [Mastering Multithreading with C++ – POSIX Threads | packtpub.com](https://www.youtube.com/watch?v=QMNtAFZtFMA)

#### Mandelbrot Calculation
- [What's so special about the Mandelbrot Set? - Numberphile](https://www.youtube.com/watch?v=FFftmWSzgmk)
- [Multithreaded Mandelbrot Renderer | C++ 11](https://www.youtube.com/watch?v=JZFOifMp6kw)
- [Let’s draw the Mandelbrot set!](https://jonisalonen.com/2013/lets-draw-the-mandelbrot-set/)

#### Xlib Usage
- [X11 C++ Tutorial - Window, Input, Drawing](https://www.youtube.com/watch?v=qZmJwk2xrJ0)
