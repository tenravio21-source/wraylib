#ifndef BALL_H
#define BALL_H

#include "raylib.h"

/* Constants */
#define BALL_RADIUS 50.0f
#define BALL_ACCELERATION 2000.0f
#define BALL_FRICTION 1800.0f
#define BALL_MAX_SPEED 300.0f
#define BALL_GRAVITY 1200.0f
#define BALL_JUMP_FORCE 600.0f
#define BALL_ELASTICITY 0.6f

/* Ball structure */
typedef struct Ball {
  Vector2 position;
  Vector2 velocity;
  float radius;
} Ball;

/* API */
void Ball_Init(Ball *ball, float x, float y);
void Ball_Update(Ball *ball, float dt, int screenWidth, int screenHeight);
void Ball_Draw(const Ball *ball);

#endif /* BALL_H */
