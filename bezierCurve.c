#include "bezierCurve.h"
#include <raylib.h>
// cubic bezier curve function; compute Point at t.
Vector2 BezierCurve(Vector2 P0, Vector2 P1, Vector2 P2, Vector2 P3, float t) {
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    Vector2 point = {
        uuu * P0.x + 3 * uu * t * P1.x + 3 * u * tt * P2.x + ttt * P3.x,
        uuu * P0.y + 3 * uu * t * P1.y + 3 * u * tt * P2.y + ttt * P3.y
    };

    return point;
}
