//
// Created by Uladzislau Lukashevich on 09/01/2022.
//

#include "functions.h"
#include "globals.h"


// is used to check collision between player and enemy
bool checkWithEnemyCollision(Enemy enemy, Player player){
    //The sides of the rectangles
    int leftE, leftP;
    int rightE, rightP;
    int topE, topP;
    int bottomE, bottomP;

    //Go through the P boxes
    for(int PBox = 0; PBox < player.numberOfHitBoxes; PBox++){
        //Calculate the sides of rect P
        leftP = player.hitBoxes[PBox].x;
        rightP = player.hitBoxes[PBox].x + player.hitBoxes[PBox].w;
        topP = player.hitBoxes[PBox].y;
        bottomP = player.hitBoxes[PBox].y + player.hitBoxes[PBox].h;

        //Go through the E boxes
        for(int EBox = 0; EBox < enemy.numberOfHitBoxes; EBox++){
            //Calculate the sides of rect B
            leftE = enemy.hitBoxes[EBox].x;
            rightE = enemy.hitBoxes[EBox].x + enemy.hitBoxes[EBox].w;
            topE = enemy.hitBoxes[EBox].y;
            bottomE = enemy.hitBoxes[EBox].y + enemy.hitBoxes[EBox].h;

            if( ( ( bottomP <= topE ) || ( topP >= bottomE ) || ( rightP <= leftE ) || ( leftP >= rightE ) ) == false )
            {
                //A collision is detected
                return true;
            }
        }
    }
    //If neither set of collision boxes touched
    return false;
}

// is used to check collision between player and enemy's bullet
bool checkWithBulletCollisionForEnemy(Bullet bullet, Player* player, Enemy enemy, Game game){
    if(player->immortality){
        return false;
    }
    int leftB, leftP;
    int rightB, rightP;
    int topB, topP;
    int bottomB, bottomP;

    leftB = bullet.x_coordinate;
    rightB = bullet.x_coordinate + bullet.width;
    topB = bullet.y_coordinate;
    bottomB = bullet.y_coordinate + bullet.height;

    //Go through the P boxes
    for(int PBox = 0; PBox < player->numberOfHitBoxes; PBox++){
        //Calculate the sides of rect P
        leftP = player->hitBoxes[PBox].x;
        rightP = player->hitBoxes[PBox].x + player->hitBoxes[PBox].w;
        topP = player->hitBoxes[PBox].y;
        bottomP = player->hitBoxes[PBox].y + player->hitBoxes[PBox].h;

        if( ( ( bottomP <= topB ) || ( topP >= bottomB ) || ( rightP <= leftB ) || ( leftP >= rightB ) ) == false )
        {
            //A collision is detected
            player->health -= enemy.damage;
            player->numberOfRecievedHits++;
            player->lastTimeOfImmortality = (int)game.worldTime;
            player->immortality = true;
            return true;
        }
    }
    //If neither set of collision boxes touched
    return false;
}

// is used to check collision between enemy and player's bullet
bool checkWithBulletCollisionForPlayer(Player* player, Bullet bullet, Enemy* enemy){
    //The sides of the rectangles
    int leftB, leftE;
    int rightB, rightE;
    int topB, topE;
    int bottomB, bottomE;

    leftB = bullet.x_coordinate;
    rightB = bullet.x_coordinate + bullet.width;
    topB = bullet.y_coordinate;
    bottomB = bullet.y_coordinate + bullet.height;

    //Go through the E boxes
    for(int EBox = 0; EBox < enemy->numberOfHitBoxes; EBox++){
        //Calculate the sides of rect B
        leftE = enemy->hitBoxes[EBox].x;
        rightE = enemy->hitBoxes[EBox].x + enemy->hitBoxes[EBox].w;
        topE = enemy->hitBoxes[EBox].y;
        bottomE = enemy->hitBoxes[EBox].y + enemy->hitBoxes[EBox].h;

        if( ( ( bottomE <= topB ) || ( topE >= bottomB ) || ( rightE <= leftB ) || ( leftE >= rightB ) ) == false )
        {
            //A collision is detected
            enemy->health -= player->damage;
            player->numberOfHits++;
            return true;
        }
    }
    //If neither set of collision boxes touched
    return false;
}

// is used to change possibility of shooting for enemy
void changePossOfShoot(Enemy* enemy, Game* game){
    if ((int)game->worldTime != game->lastWorldTime && enemy->health > 0){
        enemy->canShoot = true;
        game->lastWorldTime = (int)game->worldTime;
    }
}

// is used to load all bitmaps in start of program
void loadBmp(Sdl* sdl, Player* Player, Enemy* Enemy, Game game, Level* levels){
    // wczytanie obrazka cs8x8.bmp
    if(sdl->charset!=NULL) SDL_FreeSurface(sdl->charset);
    sdl->charset = SDL_LoadBMP("/Volumes/Macintosh HD - Data/Politechnika Gdanska/Podstawy programowania/Project/bullet_hell/cs8x8.bmp");
    if(sdl->charset == NULL) {
        printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
        exit(0);
    }
    SDL_SetColorKey(sdl->charset, true, 0x000000);

    if(sdl->player!=NULL) SDL_DestroyTexture(sdl->player);
    SDL_Surface* player = SDL_LoadBMP("/Volumes/Macintosh HD - Data/Politechnika Gdanska/Podstawy programowania/Project/bullet_hell/player3.bmp");
    if(player == NULL) {
        printf("SDL_LoadBMP(player.bmp) error: %s\n", SDL_GetError());
        exit(0);
    }else{
        Player->width = PLAYER_WIDTH;
        Player->height = PLAYER_HEIGHT;
        sdl->player = SDL_CreateTextureFromSurface(sdl->renderer, player);
        SDL_FreeSurface(player);
        player = NULL;
    }

    if(sdl->enemy!=NULL) SDL_DestroyTexture(sdl->enemy);
    char link[110];
    snprintf(link, sizeof(link), "/Volumes/Macintosh HD - Data/Politechnika Gdanska/Podstawy programowania/Project/bullet_hell/enemy%d.bmp", game.level+1);
    SDL_Surface* enemy = SDL_LoadBMP(link);
    if(enemy == NULL) {
        printf("SDL_LoadBMP(enemy%d.bmp) error: %s\n", game.level, SDL_GetError());
        exit(0);
    }else{
        Enemy->width = levels[game.level].enemyWidth;
        Enemy->height = levels[game.level].enemyHeight;
        sdl->enemy = SDL_CreateTextureFromSurface(sdl->renderer, enemy);
        SDL_FreeSurface(enemy);
        enemy = NULL;
    }

    if(sdl->enemyBullet != NULL) SDL_DestroyTexture(sdl->enemyBullet);
    SDL_Surface* enemyBullet = SDL_LoadBMP("/Volumes/Macintosh HD - Data/Politechnika Gdanska/Podstawy programowania/Project/bullet_hell/enemyBullet.bmp");
    if(enemyBullet == NULL) {
        printf("SDL_LoadBMP(enemyBullet.bmp) error: %s\n", SDL_GetError());
        exit(0);
    }else{
        Enemy->bulletWidth = enemyBullet->w; Enemy->bulletHeight = enemyBullet->h;
        sdl->enemyBullet = SDL_CreateTextureFromSurface(sdl->renderer, enemyBullet);
        SDL_FreeSurface(enemyBullet);
        enemyBullet = NULL;
    }

    if(sdl->playerBullet != NULL) SDL_DestroyTexture(sdl->playerBullet);
    SDL_Surface* playerBullet = SDL_LoadBMP("/Volumes/Macintosh HD - Data/Politechnika Gdanska/Podstawy programowania/Project/bullet_hell/playerBullet.bmp");
    if(playerBullet == NULL) {
        printf("SDL_LoadBMP(playerBullet.bmp) error: %s\n", SDL_GetError());
        exit(0);
    }else{
        Player->bulletWidth = playerBullet->w; Player->bulletHeight = playerBullet->h;
        sdl->playerBullet = SDL_CreateTextureFromSurface(sdl->renderer, playerBullet);
        SDL_FreeSurface(playerBullet);
        playerBullet = NULL;
    }

    if(sdl->bg!=NULL) SDL_DestroyTexture(sdl->bg);
    SDL_Surface* sky = SDL_LoadBMP("/Volumes/Macintosh HD - Data/Politechnika Gdanska/Podstawy programowania/Project/bullet_hell/sky.bmp");
    if(sky == NULL) {
        printf("SDL_LoadBMP(sky.bmp) error: %s\n", SDL_GetError());
        exit(0);
    }else{
        sdl->bg = SDL_CreateTextureFromSurface(sdl->renderer, sky);
        SDL_FreeSurface(sky);
        sky = NULL;
    }
}

// set x and y coordinates for each player's hitbox
void shiftHitBoxesForPlayer(Player* player){
    int r = 0;
    for(int set = 0; set < NUMBER_OF_PLAYER_HITBOXES; set++){
        player->hitBoxes[set].x = player->x_coordinate + (player->width - player->hitBoxes[set].w)/2;
        player->hitBoxes[set].y = player->y_coordinate + r;
        r += player->hitBoxes[set].h;
    }
}

// set x and y coordinates for each enemy's hitbox
void shiftHitBoxesForEnemy(Enemy* enemy){
    int r = 0;
    for(int set = 0; set < enemy->numberOfHitBoxes; set++){
        enemy->hitBoxes[set].x = enemy->x_coordinate + (enemy->width - enemy->hitBoxes[set].w)/2;
        enemy->hitBoxes[set].y = enemy->y_coordinate + r;
        r += enemy->hitBoxes[set].h;
    }
}

// handling of events during the game
void pollEvent(Sdl* sdl, int* quit, Player* player, Enemy* enemy, Game* game, Level* levels){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
                else if(event.key.keysym.sym == SDLK_UP && event.key.repeat == 0) {player->y_speed -= player->speed; player->vector = 'U';}
                else if(event.key.keysym.sym == SDLK_DOWN && event.key.repeat == 0) {player->y_speed += player->speed; player->vector = 'D';}
                else if(event.key.keysym.sym == SDLK_RIGHT && event.key.repeat == 0) {player->x_speed += player->speed; player->vector = 'R';}
                else if(event.key.keysym.sym == SDLK_LEFT && event.key.repeat == 0) {player->x_speed -= player->speed; player->vector = 'L';}
                else if(event.key.keysym.sym == SDLK_n) newGame(player, enemy, game, levels[game->level]);
                else if(event.key.keysym.sym == SDLK_l) nextLevel(sdl, player, enemy, game, levels);
                else if(event.key.keysym.sym == SDLK_SPACE) createBulletForPlayer(player);
                break;
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_UP && event.key.repeat == 0) player->y_speed += player->speed;
                else if(event.key.keysym.sym == SDLK_DOWN && event.key.repeat == 0) player->y_speed -= player->speed;
                else if(event.key.keysym.sym == SDLK_RIGHT && event.key.repeat == 0) player->x_speed -= player->speed;
                else if(event.key.keysym.sym == SDLK_LEFT && event.key.repeat == 0) player->x_speed += player->speed;
                break;
            case SDL_QUIT:
                *quit = 1;
                break;
        };
    }
}

// handling of events in menu
void pollEventForMenu(Game* game){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) game->quit = 1;
                if(event.key.keysym.sym == SDLK_1) {
                    game->mode = 'G';
                    game->level = 0;
                }
                if(event.key.keysym.sym == SDLK_2){
                    game->mode = 'G';
                    game->level = 1;
                }
                break;
            case SDL_QUIT:
                game->quit = 1;
                break;
        }
    }
}

// handling of events in special menu when player lose
void pollEventForLoseMenu(Game* game){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) game->mode = 'M';
                if(event.key.keysym.sym == SDLK_t) {
                    game->mode = 'G';
                }
                break;
            case SDL_QUIT:
                game->mode = 'M';
                break;
        }
    }
}

// handling of events in special menu when player win
void pollEventForWinMenu(Sdl* sdl, Player* player, Enemy* enemy, Game* game, Level* levels){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) game->mode = 'M';
                if(event.key.keysym.sym == SDLK_n) {
                    game->mode = 'G';
                    nextLevel(sdl, player, enemy, game, levels);
                }
                break;
            case SDL_QUIT:
                game->mode = 'M';
                break;
        }
    }
}
