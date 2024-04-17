//
// Created by Uladzislau Lukashevich on 10/01/2022.
//

#ifndef BULLET_HELL_STRUCTS_H
#define BULLET_HELL_STRUCTS_H

#include <SDL.h>

typedef struct Bullet{
    int width, height;
    double x_coordinate, y_coordinate, speed, x_speed, y_speed;
    struct Bullet *next;
}Bullet;

typedef struct EnemyAnimation{
    SDL_Rect enemyClips[5];
}EnemyAnimation;

typedef struct Enemy{
    int numberOfHitBoxes, health, damage, maxHealth, width, height, bulletWidth, bulletHeight;
    double bulletSpeed, x_coordinate, y_coordinate, timeOfDeath;
    bool canShoot;
    SDL_Rect* hitBoxes;
    Bullet* bullets;
    EnemyAnimation enemyAnimation;
}Enemy;

typedef struct PlayerAnimation{
    SDL_Rect playerClips[10];
}PlayerAnimation;

typedef struct Player{
    PlayerAnimation playerAnimation;
    bool immortality;
    char vector;
    int health, maxHealth, damage, numberOfHitBoxes, numberOfRecievedHits, numberOfHits, width, height, bulletWidth, bulletHeight, lastTimeOfImmortality;
    double bulletSpeed, x_coordinate, y_coordinate, speed, x_speed, y_speed, timeOfDeath;
    SDL_Rect* hitBoxes;
    Bullet* bullets;
}Player;

typedef struct Draw{
    char text[128];
    int czarny, zielony, czerwony, niebieski, bialy;
}Draw;

typedef struct Sdl{
    int rc;
    SDL_Surface *screen, *charset;
    SDL_Texture *scrtex, *player, *bg, *enemy, *enemyBullet, *playerBullet;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect camera;
}Sdl;

typedef struct Game{
    int t1, t2, quit, frames, lastWorldTime, level;
    double delta, worldTime, fpsTimer, fps, timeToChangeAnimation;
    char mode;
}Game;

typedef struct Icon{
    double x_coordinate, y_coordinate;
    int width, height;
    char vector;
}Icon;

typedef struct Level{
    int enemyHealth, enemyDamage, xBulletVector, xBulletSpeed, enemyWidth, enemyHeight, yBulletSpeed, yEnemyCoordinate;
    int xEnemyCoordinate, numberOfEnemyHitBoxes, *enemyHitBoxWidth, *enemyHitBoxHeight;
    double EnemyBulletSpeed;
}Level;

#endif //BULLET_HELL_STRUCTS_H
