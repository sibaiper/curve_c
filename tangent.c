#include "tangent.h"
#include <math.h>
// tangent calculation for cubic Bezier
Vector2 BezierTangent(Vector2 P0, Vector2 P1, Vector2 P2, Vector2 P3, float t) {
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;

    Vector2 tangent = {
        -3 * uu * P0.x + 3 * uu * P1.x - 6 * u * t * P1.x + 6 * u * t * P2.x - 3 * tt * P2.x + 3 * tt * P3.x,
        -3 * uu * P0.y + 3 * uu * P1.y - 6 * u * t * P1.y + 6 * u * t * P2.y - 3 * tt * P2.y + 3 * tt * P3.y
    };

    //normalize the tangent vector to get the direction
    float length = sqrt(tangent.x * tangent.x + tangent.y * tangent.y);
    tangent.x /= length;
    tangent.y /= length;

    return tangent;
}
