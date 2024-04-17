//
// Created by Uladzislau Lukashevich on 09/01/2022.
//

#ifndef BULLET_HELL_GAME_H
#define BULLET_HELL_GAME_H

#include "structs.h"

void initGame(Game* game);
void resetGame(Game* game);
void countVariables(Game* game);
void centralCamera(Sdl* sdl, Player player);
void newGame(Player* player, Enemy* enemy, Game* game, Level level);
void runGame(Game* game, Sdl* sdl, Draw draw, Player* player, Enemy* enemy, Level* levels);
void checkResult(Player* player, Enemy* enemy, Game* game);
void changeTimeToChangeAnimation(Game* game);

#endif //BULLET_HELL_GAME_H
