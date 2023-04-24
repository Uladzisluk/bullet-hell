//
// Created by Uladzislau Lukashevich on 09/01/2022.
//

#ifndef BULLET_HELL_INITIALIZATION_H
#define BULLET_HELL_INITIALIZATION_H

#include <SDL.h>
#include "structs.h"

void init(Sdl* sdl);
void clear(Sdl* sdl, Player* player, Enemy* enemy, Level* levels);

#endif //BULLET_HELL_INITIALIZATION_H
