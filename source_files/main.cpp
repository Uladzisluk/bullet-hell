#include "globals.h"

// main
int main(int argc, char **argv) {
    Sdl sdl = {0};
    Draw draw = {0};
    Game game = {0};
    Player player = {0};
    Enemy enemy = {0};
    Level* levels;
    levels = (Level*)malloc(sizeof(Level)*NUMBER_OF_LEVELS);
    for(int i=0; i<NUMBER_OF_LEVELS; i++){
        levels[i] = {0};
    }

    init(&sdl);
    initGame(&game);
    initLevels(levels);
    loadBmp(&sdl, &player, &enemy, game, levels);
    initDraw(&draw, sdl.screen);
    start(&sdl, &game, &player, &enemy, draw, levels);
    clear(&sdl, &player, &enemy, levels);

    return 0;
};
