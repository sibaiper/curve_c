#ifndef UPDATE_SPLINE_CONTROL_POINTS_H
#define UPDATE_SPLINE_CONTROL_POINTS_H

#include "raylib.h"
#include "structs.h"

void updateSplineControlPoints(Shape *shape, int numOfSplines);
bool isMouseOverPoint(Vector2 point);
#endif // UPDATE_SPLINE_CONTROL_POINTS_H
