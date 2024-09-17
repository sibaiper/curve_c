#include <raylib.h>
#include "DrawBezierCurve.h"
#include "bezierCurve.h"
#include "tangent.h"
#include "structs.h"
#include <math.h>

#define CONTROL_POINT_RADIUS 10
// draw the Bezier curve with quads
void DrawBezierCurve(Spline spline, float thickness, float step) {
    float number_of_steps = 1.0f / step;

    float hueIncrementVal = 360.0 / number_of_steps;
    float hue = 0.0;

    for (float t = 0.0f; t < 1.0f; t += step) {
        hue = fmod(hue + hueIncrementVal, 360.0);
        Color color = ColorFromHSV(hue, 0.77, 1.0);

        //points on the Bezier curve
        Vector2 currentPoint = BezierCurve(spline.P0, spline.P1, spline.P2, spline.P3, t);

        //only compute the next point and draw if t + step is within bounds
        if (true) { // I added this if statement for debugging and forgot to remove it; it is redundant of course.. but am keeping it just because
            Vector2 nextPoint = BezierCurve(spline.P0, spline.P1, spline.P2, spline.P3, t + step);

            // Tangents at the current and next points
            Vector2 currentTangent = BezierTangent(spline.P0, spline.P1, spline.P2, spline.P3, t);
            Vector2 nextTangent = BezierTangent(spline.P0, spline.P1, spline.P2, spline.P3, t + step);

            // Perpendicular vectors to the tangents
            Vector2 currentPerp = (Vector2){-currentTangent.y, currentTangent.x};
            Vector2 nextPerp = (Vector2){-nextTangent.y, nextTangent.x};

            // Points on either side of the curve (for the quad)
            Vector2 P1_current = (Vector2){currentPoint.x + (thickness / 2) * currentPerp.x, currentPoint.y + (thickness / 2) * currentPerp.y};
            Vector2 P2_current = (Vector2){currentPoint.x - (thickness / 2) * currentPerp.x, currentPoint.y - (thickness / 2) * currentPerp.y};

            Vector2 P1_next = (Vector2){nextPoint.x + (thickness / 2) * nextPerp.x, nextPoint.y + (thickness / 2) * nextPerp.y};
            Vector2 P2_next = (Vector2){nextPoint.x - (thickness / 2) * nextPerp.x, nextPoint.y - (thickness / 2) * nextPerp.y};

            // Draw two triangles to form the quad
            DrawTriangle(P1_next, P2_current, P1_current, color);
            DrawTriangle(P2_current, P1_next, P2_next, color);

            // DrawTriangleLines(P1_next, P2_current, P1_current, color);
            // DrawTriangleLines(P2_current, P1_next, P2_next, color);

            // debugging lines to visualize the points and structure
            // DrawLineV(currentPoint, nextPoint, RED);               // Curve line
            // DrawLineV(P1_current, P1_next, GREEN);                 // Top edge of quad
            // DrawLineV(P2_current, P2_next, BLUE);                  // Bottom edge of quad
        }
    }
}




void renderControlArms(Spline spline) {
  DrawLineV(spline.P0, spline.P1, GRAY);
  DrawLineV(spline.P3, spline.P2, GRAY);
}

//render multiple splines as part of a full shape
//TODO: draw curves between each spline inside the shape.
void renderShape(Shape shape_1, int numSplines, bool closeShape, float step) {
  float thickness = 55.0;
  for (int i = 0; i < numSplines; i++) {
    DrawBezierCurve(shape_1.splines[i], thickness, step);
  }

  // close the shape by connecting the last spline to the first
  if (closeShape) {
    DrawLineV(shape_1.splines[numSplines - 1].P3, shape_1.splines[0].P0,
              shape_1.splines[0].strokeColor);
  }
}

void draw_circles(Shape shape, int numOfSplines) {
  for (int i = 0; i < numOfSplines; i++) {
    DrawCircle(shape.splines[i].P0.x, shape.splines[i].P0.y,
               CONTROL_POINT_RADIUS, WHITE);
    if (!(i < numOfSplines - 1)) {
      DrawCircle(shape.splines[i].P3.x, shape.splines[i].P3.y,
                 CONTROL_POINT_RADIUS, WHITE);
    }

    DrawCircle(shape.splines[i].P1.x, shape.splines[i].P1.y,
               (int)(CONTROL_POINT_RADIUS / 2), GRAY);
    DrawCircle(shape.splines[i].P2.x, shape.splines[i].P2.y,
               (int)(CONTROL_POINT_RADIUS / 2), GRAY);
  }
}
