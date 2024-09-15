#ifndef DRAW_BEZIER_CURVE_H
#define DRAW_BEZIER_CURVE_H
#include "structs.h"
#include <raylib.h>

void DrawBezierCurve(Spline spline, float thickness, float step);
void renderControlArms(Spline spline);
void renderShape(Shape shape_1, int numSplines, bool closeShape, float);
void draw_circles(Shape shape, int numOfSplines);

#endif // DRAW_BEZIER_CURVE_H
