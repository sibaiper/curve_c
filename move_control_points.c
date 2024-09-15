#include <raylib.h>
#include "structs.h"

#define CONTROL_POINT_RADIUS 10

bool isMouseOverPoint(Vector2 point) {
  return CheckCollisionPointCircle(GetMousePosition(), point,
                                   CONTROL_POINT_RADIUS * 2);
}

void updateSplineControlPoints(Shape *shape, int numOfSplines) {
  static bool isDragging = false;
  static int selectedSpline = -1;
  static int selectedPoint = -1;
  static float dx = 0.0f, dy = 0.0f;
  static float dx2 = 0.0f, dy2 = 0.0f;

  // detect if mouse is over a control point and start dragging
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    for (int i = 0; i < numOfSplines; i++) {
      if (isMouseOverPoint(shape->splines[i].P0)) {
        isDragging = true;
        selectedSpline = i;
        selectedPoint = 0;
        dx = shape->splines[i].P1.x - shape->splines[i].P0.x;
        dy = shape->splines[i].P1.y - shape->splines[i].P0.y;

        // move the control points of the connected spline
        if (i > 0) {
          dx2 = shape->splines[i - 1].P2.x - shape->splines[i].P3.x;
          dy2 = shape->splines[i - 1].P2.y - shape->splines[i].P3.y;
        }
        break;
      }
      if (isMouseOverPoint(shape->splines[i].P3)) {
        isDragging = true;
        selectedSpline = i;
        selectedPoint = 3;
        dx = shape->splines[i].P2.x - shape->splines[i].P3.x;
        dy = shape->splines[i].P2.y - shape->splines[i].P3.y;

        // selectedPoint = P3; selectedSpline = i; that means move the P1 from
        // spline i + 1 move the control points of the connected spline
        if (i < numOfSplines - 1) {
          dx2 = shape->splines[i + 1].P1.x - shape->splines[i + 1].P0.x;
          dy2 = shape->splines[i + 1].P1.y - shape->splines[i + 1].P0.y;
        }
        break;
      }

      // handle moving control points (P1, P2)
      if (isMouseOverPoint(shape->splines[i].P1)) {
        isDragging = true;
        selectedSpline = i;
        selectedPoint = 1;
        break;
      }
      if (isMouseOverPoint(shape->splines[i].P2)) {
        isDragging = true;
        selectedSpline = i;
        selectedPoint = 2;
        break;
      }
    }
  }

  // If dragging, update the position of the selected control point
  if (isDragging && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    Vector2 mousePos = GetMousePosition();
    if (selectedPoint == 0) {
      shape->splines[selectedSpline].P0 = mousePos;
      // ensure the conected spline also moves
      if (selectedSpline > 0) {
        shape->splines[selectedSpline - 1].P3 = mousePos;

        // connect shape handles:
        shape->splines[selectedSpline - 1].P1.x = mousePos.x + dx2;
        shape->splines[selectedSpline - 1].P1.y = mousePos.y + dy2;
      }

      shape->splines[selectedSpline].P1.x = mousePos.x + dx;
      shape->splines[selectedSpline].P1.y = mousePos.y + dy;
    } else if (selectedPoint == 3) {
      shape->splines[selectedSpline].P3 = mousePos;
      // ensure the conected spline also moves
      if (selectedSpline < numOfSplines - 1) {
        shape->splines[selectedSpline + 1].P0 = mousePos;

        // selectedPoint = P3; selectedSpline = i; that means move the P1 from
        // spline i + 1
        shape->splines[selectedSpline + 1].P1.x = mousePos.x + dx2;
        shape->splines[selectedSpline + 1].P1.y = mousePos.y + dy2;
      }
      shape->splines[selectedSpline].P2.x = mousePos.x + dx;
      shape->splines[selectedSpline].P2.y = mousePos.y + dy;
    } else if (selectedPoint == 1) { // handle control points
      shape->splines[selectedSpline].P1 = mousePos;
    } else if (selectedPoint == 2) { // handle control points
      shape->splines[selectedSpline].P2 = mousePos;
    }
  }

  // stop dragging when the mouse button is released; reset vars
  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    isDragging = false;
    selectedSpline = -1;
    selectedPoint = -1;
    dx = -1.0;
    dy = -1.0;
  }
}
