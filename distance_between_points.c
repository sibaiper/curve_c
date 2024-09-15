#include "distance_between_points.h"
#include <math.h>
#include <raylib.h>

float distance_between_points(Vector2 point1, Vector2 point2) {
  return sqrt(((point2.x - point1.x) * (point2.x - point1.x)) +
              ((point2.y - point1.y) * (point2.y - point1.y)));
}
