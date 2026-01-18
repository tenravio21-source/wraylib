#include "ball.h"

void Ball_Init(Ball *ball, float x, float y) {
  ball->position = (Vector2){x, y};
  ball->velocity = (Vector2){0.0f, 0.0f};
  ball->radius = BALL_RADIUS;
}

void Ball_Update(Ball *ball, float dt, int screenWidth, int screenHeight) {
  /* Horizontal movement */
  if (IsKeyDown(KEY_D) && ball->position.x < screenWidth - ball->radius)
    ball->velocity.x = BALL_MOVE_SPEED;
  else if (IsKeyDown(KEY_A) && ball->position.x > ball->radius)
    ball->velocity.x = -BALL_MOVE_SPEED;
  else
    ball->velocity.x = 0.0f;

  /* Jump */
  bool onGround = (ball->position.y >= screenHeight - ball->radius - 1.0f);
  if (IsKeyPressed(KEY_SPACE) && onGround)
    ball->velocity.y = -BALL_JUMP_FORCE;

  /* Gravity */
  ball->velocity.y += BALL_GRAVITY * dt;

  /* Integrate velocity */
  ball->position.x += ball->velocity.x * dt;
  ball->position.y += ball->velocity.y * dt;

  /* Ground collision */
  if (ball->position.y > screenHeight - ball->radius) {
    ball->position.y = screenHeight - ball->radius;
    ball->velocity.y *= -BALL_ELASTICITY;
  }
}

void Ball_Draw(const Ball *ball) {
  DrawCircleV(ball->position, ball->radius, RED);
}
