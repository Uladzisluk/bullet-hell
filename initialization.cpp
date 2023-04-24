//
// Created by Uladzislau Lukashevich on 09/01/2022.
//

#include "initialization.h"
#include "globals.h"

// initialize all sdl features
void init(Sdl* sdl){
    printf("wyjscie printfa trafia do tego okienka\n");
    printf("printf output goes here\n");

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("SDL_Init error: %s\n", SDL_GetError());
        exit(0);
    }

    sdl->rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &sdl->window, &sdl->renderer);
    if(sdl->rc != 0) {
        SDL_Quit();
        printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
        exit(0);
    };

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(sdl->renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(sdl->renderer, 0, 0, 0, 255);
    SDL_SetWindowTitle(sdl->window, "Bullet Hell made by Uladzislau Lukashevich");
    sdl->screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    sdl->scrtex = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_ShowCursor(SDL_DISABLE);
    sdl->camera.x = 0; sdl->camera.y = 0; sdl->camera.w = SCREEN_WIDTH; sdl->camera.h = SCREEN_HEIGHT;
}

// is used to clear all storage before the end of program
void clear(Sdl* sdl, Player* player, Enemy* enemy, Level* levels){
    for(int number = 0; number<NUMBER_OF_LEVELS; number++){
        free(levels[number].enemyHitBoxHeight);
        free(levels[number].enemyHitBoxWidth);
        levels[number].enemyHitBoxWidth = NULL;
        levels[number].enemyHitBoxHeight = NULL;
    }
    free(levels);
    free(enemy->hitBoxes);
    enemy->hitBoxes = NULL;
    free(player->hitBoxes);
    player->hitBoxes = NULL;
    clearBulletsForPlayer(player);
    clearBulletsForEnemy(enemy);
    SDL_FreeSurface(sdl->screen);
    SDL_FreeSurface(sdl->charset);
    SDL_DestroyTexture(sdl->scrtex);
    SDL_DestroyWindow(sdl->window);
    SDL_DestroyRenderer(sdl->renderer);
    SDL_Quit();
}