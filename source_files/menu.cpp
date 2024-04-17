//
// Created by Uladzislau Lukashevich on 15/01/2022.
//

#include "menu.h"
#include "globals.h"

// is used to ran game menu
void runMenu(Sdl* sdl, Game* game, Draw draw, Player player){
    Icon icon = {0};
    initIcon(&icon, player);
    while(game->mode=='M' && !game->quit){
        changeIconCoordinate(&icon);
        DrawMenu(sdl, draw, icon);
        pollEventForMenu(game);
    }
}

// is used to initialize icon which will be in the menu
void initIcon(Icon* icon, Player player){
    icon->x_coordinate = START_ICON_X;
    icon->y_coordinate = START_ICON_Y;
    icon->vector = 'U';
    icon->width = player.width;
    icon->height = player.height;
}

// is used to change coordinates of icon, to make it move
void changeIconCoordinate(Icon* icon){
    if(icon->vector == 'U' && icon->y_coordinate < END_ICON_Y) icon->vector = 'D';
    else if(icon->vector == 'D' && icon->y_coordinate > START_ICON_Y) icon->vector = 'U';
    switch(icon->vector){
        case 'U':
            icon->y_coordinate -= ICON_Y_SPEED;
            icon->x_coordinate += ICON_X_SPEED;
            break;
        case 'D':
            icon->y_coordinate += ICON_Y_SPEED;
            icon->x_coordinate -= ICON_X_SPEED;
            break;
    }
}

// is used to run special menu when player lose
void runLoseMenu(Sdl* sdl, Game* game, Draw draw){
    while(game->mode == 'L' && !game->quit){
        DrawLoseMenu(sdl, draw);
        pollEventForLoseMenu(game);
    }
}

//is used to run special menu when player win
void runWinMenu(Sdl* sdl, Player* player, Enemy* enemy, Level* levels, Game* game, Draw draw){
    while(game->mode == 'W' && !game->quit){
        DrawWinMenu(sdl, draw);
        pollEventForWinMenu(sdl, player, enemy, game, levels);
    }
}