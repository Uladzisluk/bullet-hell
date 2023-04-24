//
// Created by Uladzislau Lukashevich on 13/01/2022.
//

#ifndef BULLET_HELL_LEVEL_H
#define BULLET_HELL_LEVEL_H

#include "structs.h"

void initLevels(Level* level);
void nextLevel(Sdl* sdl, Player* player, Enemy* enemy, Game* game, Level* levels);

#endif //BULLET_HELL_LEVEL_H
