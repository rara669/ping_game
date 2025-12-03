#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "paddle.h"
#include "ball.h"
#include "game.h"
#include "block.h"

int main() {
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Erreur d'initialisation SDL: %s", SDL_GetError());
        return -1;
    }

    // create window
    SDL_Window *window = SDL_CreateWindow("Ping",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               1000, 500, 0);

    if (!window) {
        SDL_Log("Erreur création fenêtre: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Erreur création renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // initialize paddle
    Paddle paddle;
    initPaddle(&paddle, 450, 480, 100, 10, 5);

    // list of Blocks
    Block blocks[3][19];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 19; j++) {
            initBlock(&blocks[i][j],20+ j * 50, 30 + i * 30, 40, 20);
        }
    }
      
    
    Ball ball;
    initBall(&ball, 490, 300, 20, 20, 5);
    // main loop
    int running = 1;
    SDL_Event event;
    
    while (running) {
        // event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = 0;
                }
            }
        }

        if (!ball.isActive ) {
            running = 0;
            gamestop(&ball, &paddle);
        }

        // Check collision between ball and paddle
        checkPaddleCollision(&ball, &paddle);

        // Update paddle and ball
        updatePaddle(&paddle, SDL_GetKeyboardState(NULL));
        updateBall(&ball);

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw paddle and ball
        drawPaddle(&paddle, renderer);
        drawBall(&ball, renderer);
        for (int i = 0; i < 3 ; i++) {
            for (int j = 0; j < 19; j++) {
                drawBlock(&blocks[i][j], renderer);
                checkBlockCollision(&blocks[i][j], &ball);
            }
        }

        // Update display
        SDL_RenderPresent(renderer);

        // Delay for ~120 FPS
        SDL_Delay(16);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

