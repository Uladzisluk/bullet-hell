//
// Created by Uladzislau Lukashevich on 13/01/2022.
//

#ifndef BULLET_HELL_ENEMY_H
#define BULLET_HELL_ENEMY_H

#include "structs.h"

void initEnemy(Enemy* enemy, Level level);
void enemyShot(Enemy* enemy, Game* game, Level level, Player* player);
void initEnemyAnimations(Enemy* enemy);

#endif //BULLET_HELL_ENEMY_H
