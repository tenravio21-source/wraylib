#include "ball.h"
#include "raylib.h"

int main(void) {
  const int screenWidth = 1080;
  const int screenHeight = 760;

  InitWindow(screenWidth, screenHeight, "raylib works");
  SetTargetFPS(60);

  Ball ball;
  Ball_Init(&ball, screenWidth / 2.0f, screenHeight - BALL_RADIUS);

  while (!WindowShouldClose()) {
    float dt = GetFrameTime();

    Ball_Update(&ball, dt, screenWidth, screenHeight);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    Ball_Draw(&ball);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
