#include "block.h"
#include <SDL2/SDL.h>
#include "ball.h"


void initBlock(Block *block, int x, int y, int w, int h) {
    block->rect.x = x;
    block->rect.y = y;
    block->rect.w = w;
    block->rect.h = h;
    block->isActive = 1;
}

void drawBlock(Block *block, SDL_Renderer *renderer) {
    if (block->isActive) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &block->rect);
    }
}

void checkBlockCollision(Block *block, Ball *ball) {
    if (block->isActive && SDL_HasIntersection(&ball->rect, &block->rect)) {
        block->isActive = 0;

        // Inverser la direction verticale de la balle
        ball->vy = -ball->vy;
    }
}
