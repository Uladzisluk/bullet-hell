//
// Created by Uladzislau Lukashevich on 15/01/2022.
//

#ifndef BULLET_HELL_MENU_H
#define BULLET_HELL_MENU_H

#include "structs.h"

void runMenu(Sdl* sdl, Game* game, Draw draw, Player player);
void initIcon(Icon* icon, Player player);
void changeIconCoordinate(Icon* icon);
void runLoseMenu(Sdl* sdl, Game* game, Draw draw);
void runWinMenu(Sdl* sdl, Player* player, Enemy* enemy, Level* levels, Game* game, Draw draw);

#endif //BULLET_HELL_MENU_H
