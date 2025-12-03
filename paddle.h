#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect rect;
    int vitesse;
    int isActive;
} Paddle;

void initPaddle(Paddle *paddle, int x, int y, int w, int h, int v);
void updatePaddle(Paddle *paddle, const Uint8 *keys);
void drawPaddle(Paddle *paddle, SDL_Renderer *renderer);

#endif