//
// Created by Uladzislau Lukashevich on 15/01/2022.
//

#include "start.h"
#include "globals.h"

// starts game
void start(Sdl* sdl, Game* game, Player* player, Enemy* enemy, Draw draw, Level* levels){
    while(!game->quit){
        if(game->mode == 'G'){
            resetGame(game);
            initLevels(levels);
            initPlayer(player);
            initEnemy(enemy, levels[game->level]);
            runGame(game, sdl, draw, player, enemy, levels);
        }else if(game->mode == 'M'){
            resetGame(game);
            runMenu(sdl, game, draw, *player);
        }else if(game->mode == 'L'){
            resetGame(game);
            runLoseMenu(sdl, game, draw);
        }else if(game->mode == 'W'){
            resetGame(game);
            runWinMenu(sdl, player, enemy, levels, game, draw);
        }
    }
}