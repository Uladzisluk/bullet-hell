//
// Created by Uladzislau Lukashevich on 09/01/2022.
//

#ifndef BULLET_HELL_GLOBALS_H
#define BULLET_HELL_GLOBALS_H

#include <cmath>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_main.h>
#include "initialization.h"
#include "drawing.h"
#include "functions.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "level.h"
#include "menu.h"
#include "start.h"

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define LENGTH_OF_HEALTH_BAR 100
#define HEIGHT_OF_HEALTH_BAR 10
#define WIDTH_OF_SYMBOL 8
#define HEIGHT_OF_SYMBOL 8
#define RATE_TO_CHANGE_ANIMATION 0.5
#define INVISIBLE_PIXEL 1000
#define HEIGHT_OF_INF_DISP 36
#define INDENT_TO_HEALTH_BAR 10
#define HEALTH_BAR_FRAME_THICKNESS 2
#define Y_INDENT_FOR_MENU 100
#define X_INDENT_FOR_MENU 100

#define NUMBER_OF_LEVELS 2

#define START_ICON_Y 100
#define START_ICON_X 200
#define ICON_Y_SPEED 0.2
#define ICON_X_SPEED 0.2
#define END_ICON_Y 30

#define NUMBER_OF_PLAYER_HITBOXES 3
#define PLAYER_WIDTH 45
#define PLAYER_HEIGHT 37
#define TIME_OF_IMMORTALITY 3

#define WORLD_WIDTH 1280
#define WORLD_HEIGHT 960

#endif //BULLET_HELL_GLOBALS_H
