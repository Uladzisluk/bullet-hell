//
// Created by Uladzislau Lukashevich on 09/01/2022.
//

#include "game.h"
#include "globals.h"

// is used to initialize all values of game
void initGame(Game* game){
    game->mode = 'M';
    game->level = 0;
    game->frames = 0;
    game->fpsTimer = 0;
    game->fps = 0;
    game->quit = 0;
    game->worldTime = 0;
    game->timeToChangeAnimation = 0;
    game->lastWorldTime = 0;
    game->t1 = SDL_GetTicks();
}

// is used to reset all values except game mode and game level
void resetGame(Game* game){
    game->frames = 0;
    game->fpsTimer = 0;
    game->fps = 0;
    game->quit = 0;
    game->worldTime = 0;
    game->lastWorldTime = 0;
    game->timeToChangeAnimation = 0;
    game->t1 = SDL_GetTicks();
}


// is used to count game variables during the game
void countVariables(Game* game){
    game->t2 = SDL_GetTicks();

    // here t2-t1 is the time in milliseconds since
    // the last screen was drawn
    // delta is the same time in seconds
    game->delta = (game->t2 - game->t1) * 0.001;
    game->t1 = game->t2;
    game->worldTime += game->delta;
    game->fpsTimer += game->delta;
    if(game->fpsTimer > 0.5) {
        game->fps = game->frames * 2;
        game->frames = 0;
        game->fpsTimer -= 0.5;
    };
}

// is used to center camera on the player
void centralCamera(Sdl* sdl, Player player){
    sdl->camera.x = ( player.x_coordinate + player.width / 2 ) - SCREEN_WIDTH / 2;
    sdl->camera.y = ( player.y_coordinate + player.height / 2 ) - SCREEN_HEIGHT / 2;

    if( sdl->camera.x < 0 ) sdl->camera.x = 0;
    if( sdl->camera.y < 0 ) sdl->camera.y = 0;
    if( sdl->camera.x > WORLD_WIDTH - sdl->camera.w ) sdl->camera.x = WORLD_WIDTH - sdl->camera.w;
    if( sdl->camera.y > WORLD_HEIGHT - sdl->camera.h ) sdl->camera.y = WORLD_HEIGHT - sdl->camera.h;
}

// is used to start new game
void newGame(Player* player, Enemy* enemy, Game* game, Level level){
    resetGame(game);
    clearBulletsForEnemy(enemy);
    clearBulletsForPlayer(player);
    initEnemy(enemy, level);
    initPlayer(player);
}

// main loop of game
void runGame(Game* game, Sdl* sdl, Draw draw, Player* player, Enemy* enemy, Level* levels){
    while(!game->quit && game->mode == 'G') {
        countVariables(game);
        movePlayer(player, *enemy, *game);
        changePlayerImmortality(player, *game);
        changeTimeToChangeAnimation(game);
        enemyShot(enemy, game, levels[game->level], player);
        playerShot(player, enemy, *game);
        centralCamera(sdl, *player);
        DrawGame(sdl, draw, *game, *player, *enemy);
        checkResult(player,enemy, game);
        pollEvent(sdl, &(game->quit), player, enemy, game, levels);
        game->frames++;
    };
}

// is used to check player's win or lose
void checkResult(Player* player, Enemy* enemy, Game* game){
    if(player->health <= 0) {
        if(player->timeOfDeath==0) player->timeOfDeath = game->worldTime;
        if(game->worldTime - player->timeOfDeath > RATE_TO_CHANGE_ANIMATION*3) game->mode = 'L';
    }
    if(enemy->health <= 0) {
        enemy->canShoot = false;
        if(enemy->timeOfDeath==0) enemy->timeOfDeath = game->worldTime;
        if(game->worldTime - enemy->timeOfDeath > RATE_TO_CHANGE_ANIMATION*3) game->mode = 'W';
    }
}

// is used to change time, which control all animations
void changeTimeToChangeAnimation(Game* game){
    if(game->worldTime - game->timeToChangeAnimation >= RATE_TO_CHANGE_ANIMATION*2) game->timeToChangeAnimation = game->worldTime;
}
