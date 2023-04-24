//
// Created by Uladzislau Lukashevich on 13/01/2022.
//

#include "bullet.h"
#include "globals.h"

void createBulletForEnemy(Enemy* enemy, Level level){
    Bullet* newBullet = (Bullet*)malloc(sizeof(Bullet));
    newBullet->y_coordinate = enemy->y_coordinate + enemy->height/5;
    newBullet->x_coordinate = enemy->x_coordinate + (level.xBulletVector)*enemy->width;
    newBullet->width = enemy->bulletWidth;
    newBullet->height = enemy->bulletHeight;
    newBullet->speed = enemy->bulletSpeed;
    newBullet->y_speed = level.yBulletSpeed;
    newBullet->x_speed = level.xBulletSpeed;
    newBullet->next = NULL;

    if(enemy->bullets==NULL){
        enemy->bullets = newBullet;
    }else{
        Bullet* wsk = enemy->bullets;
        while(wsk->next!=NULL){
            wsk = wsk->next;
        }
        wsk->next = newBullet;
    }
}

void createBulletForPlayer(Player* player){
    if(player->health <= 0) return;
    Bullet* newBullet = (Bullet*)malloc(sizeof(Bullet));
    newBullet->width = player->bulletWidth;
    newBullet->height = player->bulletHeight;
    newBullet->speed = player->bulletSpeed;
    newBullet->next = NULL;
    switch(player->vector){
        case 'U':{
            newBullet->y_speed = -newBullet->speed;
            newBullet->x_speed = 0;
            newBullet->y_coordinate = player->y_coordinate - newBullet->height;
            newBullet->x_coordinate = player->x_coordinate + (player->width - newBullet->width)/2;
            break;
        }
        case 'D':{
            newBullet->y_speed = newBullet->speed;
            newBullet->x_speed = 0;
            newBullet->y_coordinate = player->y_coordinate  + player->height;
            newBullet->x_coordinate = player->x_coordinate + (player->width - newBullet->width)/2;
            break;
        }
        case 'L':{
            newBullet->y_speed = 0;
            newBullet->x_speed = -newBullet->speed;
            newBullet->y_coordinate = player->y_coordinate  + (player->height - newBullet->height)/2;
            newBullet->x_coordinate = player->x_coordinate - newBullet->width;
            break;
        }
        case 'R':{
            newBullet->y_speed = 0;
            newBullet->x_speed = newBullet->speed;
            newBullet->y_coordinate = player->y_coordinate  + (player->height - newBullet->height)/2;
            newBullet->x_coordinate = player->x_coordinate + player->width;
            break;
        }
        default:{
            newBullet->y_speed = -newBullet->speed;
            newBullet->x_speed = 0;
            newBullet->y_coordinate = player->y_coordinate - newBullet->height;
            newBullet->x_coordinate = player->x_coordinate + (player->width - newBullet->width)/2;
            break;
        }
    }

    if(player->bullets==NULL){
        player->bullets = newBullet;
    }else{
        Bullet* wsk = player->bullets;
        while(wsk->next!=NULL){
            wsk = wsk->next;
        }
        wsk->next = newBullet;
    }
}

void moveBulletForEnemy(Enemy enemy, Game game){
    Bullet* wsk = NULL;
    if(enemy.bullets == NULL){
        return;
    }else{
        wsk = enemy.bullets;
        while(wsk->next!=NULL){
            wsk->x_coordinate += wsk->x_speed * game.delta;
            wsk->y_coordinate += wsk->y_speed * game.delta;
            wsk = wsk->next;
        }
        wsk->x_coordinate += wsk->x_speed * game.delta;
        wsk->y_coordinate += wsk->y_speed * game.delta;
    }
}

void moveBulletForPlayer(Player player, Game game){
    Bullet* wsk = NULL;
    if(player.bullets == NULL){
        return;
    }else{
        wsk = player.bullets;
        while(wsk->next!=NULL){
            wsk->x_coordinate += wsk->x_speed * game.delta;
            wsk->y_coordinate += wsk->y_speed * game.delta;
            wsk = wsk->next;
        }
        wsk->x_coordinate += wsk->x_speed * game.delta;
        wsk->y_coordinate += wsk->y_speed* game.delta;
    }
}

void checkBulletForEnemy(Enemy* enemy, Player* player, Game* game){
    int first = 1;
    Bullet* wsk = NULL;
    if(enemy->bullets == NULL){
        return;
    }else{
        wsk = enemy->bullets;
        while(wsk->next!=NULL){
            if(first && (checkWithBulletCollisionForEnemy(*wsk, player, *enemy, *game) || wsk->y_coordinate < 0 - wsk->height || wsk->y_coordinate > WORLD_HEIGHT || wsk->x_coordinate < 0 - wsk->width || wsk->x_coordinate > WORLD_WIDTH)){
                enemy->bullets = wsk->next;
                free(wsk);
                wsk = enemy->bullets;
                continue;
            }else{
                first = 0;
            }
            if(!first && (checkWithBulletCollisionForEnemy(*wsk->next, player, *enemy, *game) || wsk->y_coordinate < 0 - wsk->height || wsk->y_coordinate > WORLD_HEIGHT || wsk->x_coordinate < 0 - wsk->width || wsk->x_coordinate > WORLD_WIDTH)){
                Bullet* toDelete = wsk->next;
                wsk->next = wsk->next->next;
                free(toDelete);
                continue;
            }
            wsk = wsk->next;
        }

        if(first && (checkWithBulletCollisionForEnemy(*wsk, player, *enemy, *game) || wsk->y_coordinate < 0 - wsk->height || wsk->y_coordinate > WORLD_HEIGHT || wsk->x_coordinate < 0 - wsk->width || wsk->x_coordinate > WORLD_WIDTH)){
            enemy->bullets = wsk->next;
            free(wsk);
        }
    }
}

void checkBulletForPlayer(Player* player, Enemy* enemy){
    int first = 1;
    Bullet* wsk = NULL;
    if(player->bullets == NULL){
        return;
    }else{
        wsk = player->bullets;
        while(wsk->next!=NULL){
            if(first && (checkWithBulletCollisionForPlayer(player, *wsk, enemy) || wsk->y_coordinate < 0 - wsk->height || wsk->y_coordinate > WORLD_HEIGHT || wsk->x_coordinate < 0  - wsk->width|| wsk->x_coordinate > WORLD_WIDTH)){
                player->bullets = wsk->next;
                free(wsk);
                wsk = player->bullets;
                continue;
            }else{
                first = 0;
            }
            if(!first && (checkWithBulletCollisionForPlayer(player, *wsk->next, enemy) || wsk->y_coordinate < 0 - wsk->height || wsk->y_coordinate > WORLD_HEIGHT || wsk->x_coordinate < 0  - wsk->width|| wsk->x_coordinate > WORLD_WIDTH)){
                Bullet* toDelete = wsk->next;
                wsk->next = wsk->next->next;
                free(toDelete);
                continue;
            }
            wsk = wsk->next;
        }

        if(first && (checkWithBulletCollisionForPlayer(player, *wsk, enemy) || wsk->y_coordinate < 0 - wsk->height || wsk->y_coordinate > WORLD_HEIGHT || wsk->x_coordinate < 0  - wsk->width|| wsk->x_coordinate > WORLD_WIDTH)){
            player->bullets = wsk->next;
            free(wsk);
        }
    }
}


void clearBulletsForEnemy(Enemy* enemy){
    if(enemy->bullets == NULL) return;
    Bullet* wsk;
    while(enemy->bullets->next!=NULL){
        wsk = enemy->bullets;
        while(wsk->next->next!=NULL){
            wsk = wsk->next;
        }
        free(wsk->next);
        wsk->next = NULL;
    }
    free(enemy->bullets);
    enemy->bullets = NULL;
}

void clearBulletsForPlayer(Player* player){
    if(player->bullets==NULL) return;
    Bullet* wsk;
    while(player->bullets->next!=NULL){
        wsk = player->bullets;
        while(wsk->next->next!=NULL){
            wsk = wsk->next;
        }
        free(wsk->next);
        wsk->next = NULL;
    }
    free(player->bullets);
    player->bullets = NULL;
}