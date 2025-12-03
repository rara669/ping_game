#include <SDL2/SDL.h>
#include "ball.h"
#include "paddle.h"
#include "game.h"


void initBall(Ball *ball, int x, int y, int w, int h, int v) {
    ball->rect.x = x;
    ball->rect.y = y;
    ball->rect.w = w;
    ball->rect.h = h;
    ball->vx = 0;  // Horizontal speed
    ball->vy = v;  // Vertical speed
    ball->isActive = 1;
}


void updateBall(Ball *ball) {
    if (!ball->isActive) {
        return; 
    }
    ball->rect.x += ball->vx;
    ball->rect.y += ball->vy;

    // Check for collision with top and bottom of the window
    if (ball->rect.y <= 0) {
        ball->vy = -ball->vy; // Reverse vertical direction
    }
    if (ball->rect.y >= 500 ) {
        ball->isActive = 0;
    }
        
    // Check for collision with left and right of the window
    if (ball->rect.x <= 0 || ball->rect.x >= 1000 - ball->rect.w) {
        ball->vx = -ball->vx; // Reverse horizontal direction
    }
}

void drawBall(Ball *ball, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball->rect);
}

void applyAngle(Ball *ball, float relativeIntersection) {
    // Angle maximum (en radians, ~60°)
    float maxAngle = 1.047f; // 60° en radians
    
    // Calculate the angle based on the impact
    float angle = relativeIntersection * maxAngle;
    
    // Reset velocities with the new angle
    float speed = 5.0f; // Constant speed
    ball->vx = sin(angle) * speed;
    ball->vy = -cos(angle) * speed; // Always upwards
}

void checkPaddleCollision(Ball *ball, Paddle *paddle) {
    if (SDL_HasIntersection(&ball->rect, &paddle->rect)) {
        // 1. Find where the ball hit the paddle
        float ballCenter = ball->rect.x + ball->rect.w / 2.0f;
        float paddleCenter = paddle->rect.x + paddle->rect.w / 2.0f;
        
        // 2. Calculate the relative distance (-1 to 1)
        float relativeIntersection = (ballCenter - paddleCenter) / (paddle->rect.w / 2.0f);
        
        // 3. Limit between -1 and 1
        if (relativeIntersection < -1.0f) relativeIntersection = -1.0f;
        if (relativeIntersection > 1.0f) relativeIntersection = 1.0f;
        
        // 4. Apply the angle
        applyAngle(ball, relativeIntersection);
        
        // 5. Reposition the ball above the paddle
        ball->rect.y = paddle->rect.y - ball->rect.h;
    }

}