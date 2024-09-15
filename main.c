#include <raylib.h>
#include <stdbool.h>
#include "structs.h"
#include "DrawBezierCurve.h"
#include "move_control_points.h"


float lerp(float start, float end, float t);

int main() {

  InitWindow(800, 600, "quads");
  SetTargetFPS(60);

  float startTime = 0.0f;
  bool animating = false;

  float start_step = 0.1;
  float end_step = 0.01;
  float duration = 5.0f;  //duration in seconds


  //random splines
  Spline spline_1 = {{100, 500},
                     {150, 200},
                     {400, 100},
                     {600, 300},
                     RED};
  Spline spline_2 = {{600, 300},
                     {650, 500},
                     {500, 600},
                     {300, 500},
                     GREEN};
  Spline spline_3 = {{300, 500},
                     {150, 400},
                     {200, 300},
                     {400, 250},
                     BLUE};
  Spline spline_4 = {{400, 250},
                     {450, 150},
                     {600, 50},
                     {700, 300},
                     ORANGE};

  Spline splines[] = {spline_1};

  Shape shape_1 = {splines, 1};

  bool closeShape = false;

  float thickness = 20.0f;
  bool drawControlPoints = true;
  bool finishedAnimating = false;
  float step = start_step;


  while (!WindowShouldClose()) {

    // start the animation
    if (IsKeyPressed(KEY_SPACE)) {
      startTime = GetTime();
      animating = true;
    }

    // calculate the elapsed time since animation started
    float currentTime = GetTime();
    float elapsed = currentTime - startTime;

    // calculate animation progress (0.0 to 1.0)
    float t = elapsed / duration;

    // calculate the current step @ t.
    if(finishedAnimating == true) {
        step = end_step;
    }
    if (animating) {
      if (t >= 1.0f) { //clean up after animation ended
        animating = false;
        t = 1.0f;
        finishedAnimating = true;
      }
      finishedAnimating = false;
      step = lerp(start_step, end_step, t);
    }

    if (IsKeyPressed(84)) {
      drawControlPoints = !drawControlPoints;
    }

    BeginDrawing();
    ClearBackground(BLACK);


    // render the curve
    renderShape(shape_1, shape_1.numOfSplines, closeShape, step);
    if (drawControlPoints == true) {
      for (int i = 0; i < shape_1.numOfSplines; i++) {
        renderControlArms(shape_1.splines[i]);
      }
      draw_circles(shape_1, shape_1.numOfSplines);
      //handle moving circles if the arms and circles are drawn
      updateSplineControlPoints(&shape_1, shape_1.numOfSplines);
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

float lerp(float start, float end, float t) {
  return start + t * (end - start);
}
