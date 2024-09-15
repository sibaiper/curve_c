#ifndef SHAPES_H
#define SHAPES_H

#include "raylib.h"

typedef struct Spline {
    Vector2 P0;
    Vector2 P1;
    Vector2 P2;
    Vector2 P3;
    Color strokeColor;
} Spline;

typedef struct Shape {
    Spline *splines;
    int numOfSplines;
} Shape;

#endif // SHAPES_H
