#include <SDL2/SDL.h>
#include "paddle.h"

void initPaddle(Paddle *paddle, int x, int y, int w, int h, int v) {
    paddle->rect.x = x;
    paddle->rect.y = y;
    paddle->rect.w = w;
    paddle->rect.h = h;
    paddle->vitesse = v;
    paddle->isActive = 1; // Paddle is active
}

void updatePaddle(Paddle *paddle, const Uint8 *keys) {
    if (!paddle->isActive) {
        return; 
    }
    if (keys[SDL_SCANCODE_LEFT]) {
        paddle->rect.x -= paddle->vitesse;
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        paddle->rect.x += paddle->vitesse;
    }

    // limit paddle within window bounds
    if (paddle->rect.x < 0) paddle->rect.x = 0;
    if (paddle->rect.x + paddle->rect.w > 1000) paddle->rect.x = 1000 - paddle->rect.w;
}

void drawPaddle(Paddle *paddle, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle->rect);
}