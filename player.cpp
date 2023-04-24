//
// Created by Uladzislau Lukashevich on 10/01/2022.
//

#include "player.h"
#include "globals.h"

// initialization of player values
void initPlayer(Player* player){
    player->numberOfHitBoxes = NUMBER_OF_PLAYER_HITBOXES;
    player->numberOfHits = 0;
    player->numberOfRecievedHits = 0;
    player->health = 100;
    player->maxHealth = player->health;
    player->damage = 10;
    player->timeOfDeath = 0;
    player->lastTimeOfImmortality = 0;
    player->hitBoxes = (SDL_Rect*)malloc(sizeof(SDL_Rect)*NUMBER_OF_PLAYER_HITBOXES);
    player->x_coordinate = WORLD_WIDTH/2;
    player->y_coordinate = WORLD_HEIGHT/2;
    player->speed = 300;
    player->immortality = false;
    player->bullets = NULL;
    player->bulletSpeed = 500;
    player->vector = 'L';
    player->x_speed = 0;
    player->y_speed = 0;
    player->hitBoxes[0].w = 24;
    player->hitBoxes[0].h = 9;
    player->hitBoxes[1].w = 38;
    player->hitBoxes[1].h = 20;
    player->hitBoxes[2].w = 23;
    player->hitBoxes[2].h = 8;
    shiftHitBoxesForPlayer(player);
    initPlayerAnimations(player);
}

// change player coordinates during the game
void movePlayer(Player* player, Enemy enemy, Game game){
    if(player->health <= 0) return;
    player->x_coordinate += player->x_speed * game.delta;
    shiftHitBoxesForPlayer(player);

    if( (player->x_coordinate < 0) || (player->x_coordinate + player->width > WORLD_WIDTH) || checkWithEnemyCollision(enemy,*player)){
        player->x_coordinate -= player->x_speed * game.delta;
        shiftHitBoxesForPlayer(player);
    }

    player->y_coordinate += player->y_speed * game.delta;
    shiftHitBoxesForPlayer(player);

    if( (player->y_coordinate < HEIGHT_OF_INF_DISP+4) || (player->y_coordinate + player->width > WORLD_HEIGHT) || checkWithEnemyCollision(enemy, *player)){
        player->y_coordinate -= player->y_speed * game.delta;
        shiftHitBoxesForPlayer(player);
    }
}

// is used to control shots of player
void playerShot(Player* player, Enemy* enemy, Game game){
    moveBulletForPlayer(*player, game);
    checkBulletForPlayer(player, enemy);
}

// is used to change player immortality
void changePlayerImmortality(Player* player, Game game){
    if(!player->immortality) return;
    if((int)game.worldTime - player->lastTimeOfImmortality == TIME_OF_IMMORTALITY){
        player->immortality = false;
    }
}

// initialize each clip value of player animation
void initPlayerAnimations(Player* player){
    player->playerAnimation.playerClips[0].x = 0;
    player->playerAnimation.playerClips[0].y = 0;
    player->playerAnimation.playerClips[0].w = PLAYER_WIDTH;
    player->playerAnimation.playerClips[0].h = PLAYER_HEIGHT;

    player->playerAnimation.playerClips[1].x = PLAYER_WIDTH;
    player->playerAnimation.playerClips[1].y = 0;
    player->playerAnimation.playerClips[1].w = 65;
    player->playerAnimation.playerClips[1].h = PLAYER_HEIGHT;

    player->playerAnimation.playerClips[2].x = 109;
    player->playerAnimation.playerClips[2].y = 0;
    player->playerAnimation.playerClips[2].w = 74;
    player->playerAnimation.playerClips[2].h = PLAYER_HEIGHT;

    player->playerAnimation.playerClips[3].x = 187;
    player->playerAnimation.playerClips[3].y = 0;
    player->playerAnimation.playerClips[3].w = 65;
    player->playerAnimation.playerClips[3].h = PLAYER_HEIGHT;

    player->playerAnimation.playerClips[4].x = 253;
    player->playerAnimation.playerClips[4].y = 0;
    player->playerAnimation.playerClips[4].w = 74;
    player->playerAnimation.playerClips[4].h = PLAYER_HEIGHT;

    player->playerAnimation.playerClips[5].x = 328;
    player->playerAnimation.playerClips[5].y = 0;
    player->playerAnimation.playerClips[5].w = PLAYER_WIDTH;
    player->playerAnimation.playerClips[5].h = PLAYER_HEIGHT;

    player->playerAnimation.playerClips[6].x = 374;
    player->playerAnimation.playerClips[6].y = 0;
    player->playerAnimation.playerClips[6].w = PLAYER_WIDTH;
    player->playerAnimation.playerClips[6].h = PLAYER_HEIGHT;

    player->playerAnimation.playerClips[7].x = 418;
    player->playerAnimation.playerClips[7].y = 0;
    player->playerAnimation.playerClips[7].w = PLAYER_WIDTH;
    player->playerAnimation.playerClips[7].h = PLAYER_HEIGHT;

    player->playerAnimation.playerClips[8].x = 464;
    player->playerAnimation.playerClips[8].y = 0;
    player->playerAnimation.playerClips[8].w = PLAYER_WIDTH;
    player->playerAnimation.playerClips[8].h = PLAYER_HEIGHT;

    player->playerAnimation.playerClips[9].x = 509;
    player->playerAnimation.playerClips[9].y = 0;
    player->playerAnimation.playerClips[9].w = PLAYER_WIDTH;
    player->playerAnimation.playerClips[9].h = PLAYER_HEIGHT;
}
