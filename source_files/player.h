//
// Created by Uladzislau Lukashevich on 10/01/2022.
//

#ifndef BULLET_HELL_PLAYER_H
#define BULLET_HELL_PLAYER_H

#include "structs.h"

void initPlayer(Player* player);
void movePlayer(Player* player, Enemy enemy, Game game);
void playerShot(Player* player, Enemy* enemy, Game game);
void changePlayerImmortality(Player* player, Game game);
void initPlayerAnimations(Player* player);

#endif //BULLET_HELL_PLAYER_H
