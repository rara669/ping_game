#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include "ball.h"

typedef struct {
    SDL_Rect rect;
    int x;
    int y;
    int w;
    int h;
    int isActive;
} Block;

void initBlock(Block *block, int x, int y, int w, int h);
void drawBlock(Block *block, SDL_Renderer *renderer);
void checkBlockCollision(Block *block, Ball *ball);


#endif