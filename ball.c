#include "ball.h"

void Ball_Init(Ball *ball, float x, float y) {
  ball->position = (Vector2){x, y};
  ball->velocity = (Vector2){0.0f, 0.0f};
  ball->radius = BALL_RADIUS;
}

void Ball_Update(Ball *ball, float dt, int screenWidth, int screenHeight) {
  /* -----------------------------
     INPUT (HORIZONTAL)
     ----------------------------- */
  float inputX = 0.0f;

  if (IsKeyDown(KEY_D))
    inputX += 1.0f;
  if (IsKeyDown(KEY_A))
    inputX -= 1.0f;

  /* -----------------------------
     ACCELERATION (SMOOTH START)
     ----------------------------- */
  ball->velocity.x += inputX * BALL_ACCELERATION * dt;

  /* -----------------------------
     FRICTION (SMOOTH STOP)
     ----------------------------- */
  if (inputX == 0.0f) {
    if (ball->velocity.x > 0.0f) {
      ball->velocity.x -= BALL_FRICTION * dt;
      if (ball->velocity.x < 0.0f)
        ball->velocity.x = 0.0f;
    } else if (ball->velocity.x < 0.0f) {
      ball->velocity.x += BALL_FRICTION * dt;
      if (ball->velocity.x > 0.0f)
        ball->velocity.x = 0.0f;
    }
  }

  /* -----------------------------
     CLAMP MAX SPEED
     ----------------------------- */
  if (ball->velocity.x > BALL_MAX_SPEED)
    ball->velocity.x = BALL_MAX_SPEED;
  else if (ball->velocity.x < -BALL_MAX_SPEED)
    ball->velocity.x = -BALL_MAX_SPEED;

  /* -----------------------------
     JUMP
     ----------------------------- */
  bool onGround = (ball->position.y >= screenHeight - ball->radius - 1.0f);
  if (IsKeyPressed(KEY_SPACE) && onGround)
    ball->velocity.y = -BALL_JUMP_FORCE;

  /* -----------------------------
     GRAVITY
     ----------------------------- */
  ball->velocity.y += BALL_GRAVITY * dt;

  /* -----------------------------
     INTEGRATE VELOCITY → POSITION
     ----------------------------- */
  ball->position.x += ball->velocity.x * dt;
  ball->position.y += ball->velocity.y * dt;

  /* -----------------------------
     SCREEN BOUNDS (LEFT / RIGHT)
     ----------------------------- */
  if (ball->position.x < ball->radius) {
    ball->position.x = ball->radius;
    ball->velocity.x = 0.0f;
  } else if (ball->position.x > screenWidth - ball->radius) {
    ball->position.x = screenWidth - ball->radius;
    ball->velocity.x = 0.0f;
  }

  /* -----------------------------
     GROUND COLLISION
     ----------------------------- */
  if (ball->position.y > screenHeight - ball->radius) {
    ball->position.y = screenHeight - ball->radius;
    ball->velocity.y *= -BALL_ELASTICITY;
  }
}

void Ball_Draw(const Ball *ball) {
  DrawCircleV(ball->position, ball->radius, RED);
}
