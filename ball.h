#ifndef BALL_H
#define BALL_H

#include "paddle.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect rect;
    int dx;
    int dy;
    int vx;
    int vy;
    int isActive;
} Ball;

void initBall(Ball *ball, int x, int y, int w, int h, int v);
void updateBall(Ball *ball);
void drawBall(Ball *ball, SDL_Renderer *renderer);
void checkPaddleCollision(Ball *ball, Paddle *paddle);
void applyAngle(Ball *ball, float relativeIntersection);


#endif