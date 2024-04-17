//
// Created by Uladzislau Lukashevich on 09/01/2022.
//

#ifndef BULLET_HELL_FUNCTIONS_H
#define BULLET_HELL_FUNCTIONS_H

#include "structs.h"

bool checkWithEnemyCollision(Enemy enemy, Player player);
bool checkWithBulletCollisionForEnemy(Bullet bullet, Player* player, Enemy enemy, Game game);
bool checkWithBulletCollisionForPlayer(Player* player, Bullet bullet, Enemy* enemy);
void changePossOfShoot(Enemy* enemy, Game* game);
void loadBmp(Sdl* sdl, Player* Player, Enemy* Enemy, Game game, Level* levels);
void shiftHitBoxesForPlayer(Player* player);
void shiftHitBoxesForEnemy(Enemy* enemy);
void pollEvent(Sdl* sdl, int* quit, Player* player, Enemy* enemy, Game* game, Level* levels);
void pollEventForMenu(Game* game);
void pollEventForLoseMenu(Game* game);
void pollEventForWinMenu(Sdl* sdl, Player* player, Enemy* enemy, Game* game, Level* levels);

#endif //BULLET_HELL_FUNCTIONS_H
