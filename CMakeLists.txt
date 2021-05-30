cmake_minimum_required(VERSION 3.19)
project(mandelbrot_fractal)

set(CMAKE_CXX_STANDARD 14)

find_package(X11 REQUIRED)
message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")
include_directories(${X11_INCLUDE_DIR})

add_executable(mandelbrot_fractal main.cpp)
target_link_libraries(mandelbrot_fractal ${X11_LIBRARIES})
