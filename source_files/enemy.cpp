//
// Created by Uladzislau Lukashevich on 13/01/2022.
//

#include "enemy.h"
#include "globals.h"

// initialization of enemy values
void initEnemy(Enemy* enemy, Level level){
    enemy->numberOfHitBoxes = level.numberOfEnemyHitBoxes;
    enemy->hitBoxes = (SDL_Rect*)malloc(sizeof(SDL_Rect)*level.numberOfEnemyHitBoxes);
    enemy->y_coordinate =  level.yEnemyCoordinate - enemy->height/2;
    enemy->x_coordinate = level.xEnemyCoordinate;
    enemy->health = level.enemyHealth;
    enemy->timeOfDeath = 0;
    enemy->maxHealth = level.enemyHealth;
    enemy->damage = level.enemyDamage;
    enemy->bullets = NULL;
    enemy->bulletSpeed = level.EnemyBulletSpeed;
    enemy->canShoot = false ;
    for (int i = 0; i < level.numberOfEnemyHitBoxes; i++){
        enemy->hitBoxes[i].w = level.enemyHitBoxWidth[i];
        enemy->hitBoxes[i].h = level.enemyHitBoxHeight[i];
    }
    shiftHitBoxesForEnemy(enemy);
    initEnemyAnimations(enemy);
}

// is used to control shots of enemy
void enemyShot(Enemy* enemy, Game* game, Level level, Player* player){
    changePossOfShoot(enemy, game);
    if((int)game->worldTime % 1 == 0 && enemy->canShoot){
        createBulletForEnemy(enemy, level);
        enemy->canShoot = false;
    }
    moveBulletForEnemy(*enemy, *game);
    checkBulletForEnemy(enemy, player, game);
}

// initialize each clip value of enemy animation
void initEnemyAnimations(Enemy* enemy){
    enemy->enemyAnimation.enemyClips[0].x = 0;
    enemy->enemyAnimation.enemyClips[0].y = 0;
    enemy->enemyAnimation.enemyClips[0].w = enemy->width;
    enemy->enemyAnimation.enemyClips[0].h = enemy->height;

    enemy->enemyAnimation.enemyClips[1].x = enemy->width;
    enemy->enemyAnimation.enemyClips[1].y = 0;
    enemy->enemyAnimation.enemyClips[1].w = enemy->width;
    enemy->enemyAnimation.enemyClips[1].h = enemy->height;

    enemy->enemyAnimation.enemyClips[2].x = enemy->width*2;
    enemy->enemyAnimation.enemyClips[2].y = 0;
    enemy->enemyAnimation.enemyClips[2].w = enemy->width;
    enemy->enemyAnimation.enemyClips[2].h = enemy->height;

    enemy->enemyAnimation.enemyClips[3].x = enemy->width*3;
    enemy->enemyAnimation.enemyClips[3].y = 0;
    enemy->enemyAnimation.enemyClips[3].w = enemy->width;
    enemy->enemyAnimation.enemyClips[3].h = enemy->height;

    enemy->enemyAnimation.enemyClips[4].x = enemy->width*4;
    enemy->enemyAnimation.enemyClips[4].y = 0;
    enemy->enemyAnimation.enemyClips[4].w = enemy->width;
    enemy->enemyAnimation.enemyClips[4].h = enemy->height;
}