//
// Created by Uladzislau Lukashevich on 13/01/2022.
//

#ifndef BULLET_HELL_BULLET_H
#define BULLET_HELL_BULLET_H

#include "structs.h"

void createBulletForEnemy(Enemy* enemy, Level level);
void createBulletForPlayer(Player* player);
void moveBulletForEnemy(Enemy enemy, Game game);
void moveBulletForPlayer(Player player, Game game);
void checkBulletForEnemy(Enemy* enemy, Player* player, Game* game);
void checkBulletForPlayer(Player* player, Enemy* enemy);
void clearBulletsForEnemy(Enemy* enemy);
void clearBulletsForPlayer(Player* player);

#endif //BULLET_HELL_BULLET_H
