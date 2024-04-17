//
// Created by Uladzislau Lukashevich on 13/01/2022.
//

#include "level.h"
#include "globals.h"

// initialize all variables for each level
void initLevels(Level* level){
    for(int i=0; i<NUMBER_OF_LEVELS; i++){
        switch(i){
            case 0:{
                level[i].xBulletVector = 1;
                level[i].EnemyBulletSpeed = 400;
                level[i].xBulletSpeed = level[i].EnemyBulletSpeed;
                level[i].yBulletSpeed = 0;
                level[i].yEnemyCoordinate = WORLD_HEIGHT/2;
                level[i].xEnemyCoordinate = 100;
                level[i].enemyHealth = 200;
                level[i].enemyDamage = 20;
                level[i].numberOfEnemyHitBoxes = 4;
                level[i].enemyWidth = 90;
                level[i].enemyHeight = 72;
                level[i].enemyHitBoxWidth = (int*)malloc(sizeof(int)*level[i].numberOfEnemyHitBoxes);
                level[i].enemyHitBoxHeight = (int*)malloc(sizeof(int)*level[i].numberOfEnemyHitBoxes);
                level[i].enemyHitBoxWidth[0] = 52; level[i].enemyHitBoxHeight[0] = 14;
                level[i].enemyHitBoxWidth[1] = 87, level[i].enemyHitBoxHeight[1] = 15;
                level[i].enemyHitBoxWidth[2] = 64; level[i].enemyHitBoxHeight[2] = 20;
                level[i].enemyHitBoxWidth[3] = 39; level[i].enemyHitBoxHeight[3] = 23;
                break;
            }
            case 1:{
                level[i].xBulletVector = -1;
                level[i].EnemyBulletSpeed = 400;
                level[i].xBulletSpeed = -level[i].EnemyBulletSpeed;
                level[i].yBulletSpeed = 0;
                level[i].yEnemyCoordinate = WORLD_HEIGHT/2;
                level[i].xEnemyCoordinate = WORLD_WIDTH - 200;
                level[i].enemyHealth = 500;
                level[i].enemyDamage = 30;
                level[i].numberOfEnemyHitBoxes = 4;
                level[i].enemyWidth = 90;
                level[i].enemyHeight = 72;
                level[i].enemyHitBoxWidth = (int*)malloc(sizeof(int)*level[i].numberOfEnemyHitBoxes);
                level[i].enemyHitBoxHeight = (int*)malloc(sizeof(int)*level[i].numberOfEnemyHitBoxes);
                level[i].enemyHitBoxWidth[0] = 52; level[i].enemyHitBoxHeight[0] = 14;
                level[i].enemyHitBoxWidth[1] = 87, level[i].enemyHitBoxHeight[1] = 15;
                level[i].enemyHitBoxWidth[2] = 64; level[i].enemyHitBoxHeight[2] = 20;
                level[i].enemyHitBoxWidth[3] = 39; level[i].enemyHitBoxHeight[3] = 23;
                break;
            }
            default:{
                level[i].xBulletVector = 1;
                level[i].EnemyBulletSpeed = 400;
                level[i].xBulletSpeed = level[i].EnemyBulletSpeed;
                level[i].yBulletSpeed = 0;
                level[i].yEnemyCoordinate = WORLD_HEIGHT/2;
                level[i].xEnemyCoordinate = 100;
                level[i].enemyHealth = 200;
                level[i].enemyDamage = 20;
                level[i].numberOfEnemyHitBoxes = 4;
                level[i].enemyWidth = 90;
                level[i].enemyHeight = 72;
                level[i].enemyHitBoxWidth = (int*)malloc(sizeof(int)*level[i].numberOfEnemyHitBoxes);
                level[i].enemyHitBoxHeight = (int*)malloc(sizeof(int)*level[i].numberOfEnemyHitBoxes);
                level[i].enemyHitBoxWidth[0] = 52; level[i].enemyHitBoxHeight[0] = 14;
                level[i].enemyHitBoxWidth[1] = 87, level[i].enemyHitBoxHeight[1] = 15;
                level[i].enemyHitBoxWidth[2] = 64; level[i].enemyHitBoxHeight[2] = 20;
                level[i].enemyHitBoxWidth[3] = 39; level[i].enemyHitBoxHeight[3] = 23;
                break;
            }
        }
    }
}

// is used to go to next level
void nextLevel(Sdl* sdl, Player* player, Enemy* enemy, Game* game, Level* levels){
    resetGame(game);
    game->level++;
    if (game->level>NUMBER_OF_LEVELS-1) game->level = 0;
    loadBmp(sdl, player, enemy, *game, levels);
    clearBulletsForEnemy(enemy);
    clearBulletsForPlayer(player);
    initEnemy(enemy, levels[game->level]);
    initPlayer(player);
}