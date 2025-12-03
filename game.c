#include <SDL2/SDL.h>
#include "game.h"
#include "ball.h"
#include "paddle.h"

void gamestop(Ball *ball, Paddle *paddle) {
    paddle->isActive = 0;
    ball->isActive = 0;
    SDL_Log("Game Over! Ball went out of bounds.");
    
}