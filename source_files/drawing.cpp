#define _CRT_SECURE_NO_WARNINGS
//
// Created by Uladzislau Lukashevich on 09/01/2022.
//

#include "drawing.h"
#include "globals.h"

// initialization of colors to draw
void initDraw(Draw* draw, SDL_Surface* screen) {
    draw->czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
    draw->zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
    draw->czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
    draw->niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
    draw->bialy = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
}

// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface *screen, int x, int y, const char *text, SDL_Surface *charset) {
    int px, py, c;
    SDL_Rect s, d;
    s.w = WIDTH_OF_SYMBOL;
    s.h = HEIGHT_OF_SYMBOL;
    d.w = WIDTH_OF_SYMBOL;
    d.h = HEIGHT_OF_SYMBOL;
    while(*text) {
        c = *text & 255;
        px = (c % 16) * WIDTH_OF_SYMBOL;
        py = (c / 16) * HEIGHT_OF_SYMBOL;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(charset, &s, screen, &d);
        x += WIDTH_OF_SYMBOL;
        text++;
    };
};


// draw a player sprite on a surface screen
void DrawPlayer(Sdl* sdl, Player player, Game game){
    SDL_Rect dest;
    SDL_Rect* source;
    int whichClip = 0;
    dest.x = player.x_coordinate - sdl->camera.x;
    dest.y = player.y_coordinate - sdl->camera.y;
    dest.w = player.width;
    dest.h = player.height;
    if(player.health > 0){
        if(player.x_speed == 0 && player.y_speed == 0) {
            whichClip = 0;
            dest.w = player.playerAnimation.playerClips[0].w;
        }else{
            switch(player.vector){
                case 'L':{
                    if (game.worldTime - game.timeToChangeAnimation < RATE_TO_CHANGE_ANIMATION){
                        whichClip = 1;
                        dest.w = player.playerAnimation.playerClips[1].w;
                    }
                    else{
                        whichClip = 2;
                        dest.x = player.x_coordinate - sdl->camera.x-2;
                        dest.w = player.playerAnimation.playerClips[2].w;
                    }
                    break;
                }
                case 'R':{
                    if (game.worldTime - game.timeToChangeAnimation < RATE_TO_CHANGE_ANIMATION){
                        whichClip = 3;
                        dest.x = player.x_coordinate - sdl->camera.x - 21;
                        dest.w = player.playerAnimation.playerClips[1].w;
                    }
                    else {
                        whichClip = 4;
                        dest.x = player.x_coordinate - sdl->camera.x - 30;
                        dest.w = player.playerAnimation.playerClips[2].w;
                    }
                    break;
                }
                default: {
                    if (game.worldTime - game.timeToChangeAnimation < RATE_TO_CHANGE_ANIMATION) {
                        whichClip = 5;
                        dest.w = player.playerAnimation.playerClips[5].w;
                    }
                    else {
                        whichClip = 6;
                        dest.w = player.playerAnimation.playerClips[6].w;
                    }
                    break;
                }
            }
        }
    }else{
        if(game.worldTime - player.timeOfDeath < RATE_TO_CHANGE_ANIMATION) whichClip = 7;
        else if(game.worldTime - player.timeOfDeath < RATE_TO_CHANGE_ANIMATION*2) whichClip = 8;
        else whichClip = 9;
    }

    source = &player.playerAnimation.playerClips[whichClip];
    SDL_RenderCopy(sdl->renderer, sdl->player, source, &dest);
}

// draw a enemy sprite on a surface screen
void DrawEnemy(Sdl* sdl, Enemy enemy, Game game){
    SDL_Rect dest;
    SDL_Rect* source;
    int whichClip = 0;
    if(enemy.health >0){
        if (game.worldTime - game.timeToChangeAnimation < RATE_TO_CHANGE_ANIMATION){
            whichClip = 0;
        }
        else{
            whichClip = 1;
        }
    }else{
        if(game.worldTime - enemy.timeOfDeath < RATE_TO_CHANGE_ANIMATION) whichClip = 2;
        else if(game.worldTime - enemy.timeOfDeath < RATE_TO_CHANGE_ANIMATION*2) whichClip = 3;
        else whichClip = 4;
    }
    source = &enemy.enemyAnimation.enemyClips[whichClip];
    dest.x = enemy.x_coordinate - sdl->camera.x;
    dest.y = enemy.y_coordinate - sdl->camera.y;
    dest.w = enemy.width;
    dest.h = enemy.height;
    SDL_RenderCopy(sdl->renderer, sdl->enemy, source, &dest);
}

// draw a enemy's bullet sprite on a surface screen
void DrawBulletForEnemy(Sdl* sdl, Enemy enemy){
    if(enemy.bullets==NULL){
        return;
    }

    SDL_Rect dest;
    Bullet* wsk = enemy.bullets;
    while(wsk!=NULL){
        dest.x = wsk->x_coordinate - sdl->camera.x;
        dest.y = wsk->y_coordinate - sdl->camera.y;
        dest.w = wsk->width;
        dest.h = wsk->height;
        SDL_RenderCopy(sdl->renderer, sdl->enemyBullet, NULL, &dest);
        wsk = wsk->next;
    }
}

// draw a player's bullet sprite on a surface screen
void DrawBulletForPlayer(Sdl* sdl, Player player){
    if(player.bullets==NULL){
        return;
    }
    SDL_Rect dest;
    Bullet* wsk = player.bullets;
    while(wsk!=NULL){
        dest.x = wsk->x_coordinate - sdl->camera.x;
        dest.y = wsk->y_coordinate - sdl->camera.y;
        dest.w = wsk->width;
        dest.h = wsk->height;
        SDL_RenderCopy(sdl->renderer, sdl->playerBullet, NULL, &dest);
        wsk = wsk->next;
    }
}

// draw a single pixel
void DrawPixel(SDL_Surface surface, int x, int y, Uint32 color) {
    int bpp = surface.format->BytesPerPixel;
    if (x<0) x = INVISIBLE_PIXEL;
    if(y<0) y = INVISIBLE_PIXEL;
    Uint8 *p = (Uint8 *)surface.pixels + y * surface.pitch + x * bpp;
    *(Uint32 *)p = color;
};

// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface screen, int x, int y, int l, int dx, int dy, Uint32 color) {
    for(int i = 0; i < l; i++) {
        DrawPixel(screen, x, y, color);
        x += dx;
        y += dy;
    };
};

// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
    int i;
    DrawLine(screen, x, y, k, 0, 1, outlineColor);
    DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
    DrawLine(screen, x, y, l, 1, 0, outlineColor);
    DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
    for(i = y + 1; i < y + k - 1; i++)
        DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

// draw a sky
void DrawSky(Sdl* sdl){
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = sdl->camera.w;
    dest.h = sdl->camera.h;
    SDL_RenderCopy(sdl->renderer, sdl->bg, &sdl->camera, &dest);
}

// draw a background
void DrawBackGround(Sdl* sdl){
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = sdl->camera.w;
    dest.h = sdl->camera.h;
    SDL_RenderCopy(sdl->renderer, sdl->bg, NULL, &dest);
}

// draw a display where will be displayed information
void DrawInfDisplay(Sdl* sdl, Draw draw, Game game){
    // info text
    DrawRectangle(*sdl->screen, 4, 4, SCREEN_WIDTH - 8, HEIGHT_OF_INF_DISP, draw.czerwony, draw.niebieski);
    // "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
    sprintf(draw.text, "Time elapsed from the start of the level : %.1lf s  %.0lf klatek / s", game.worldTime, game.fps);
    DrawString(sdl->screen, sdl->screen->w / 2 - strlen(draw.text) * WIDTH_OF_SYMBOL / 2, 10, draw.text, sdl->charset);
    // "Esc - exit, \030 - faster, \031 - slower"
    sprintf(draw.text, "Esc - quit, N - new game, \030 - Up, \031 - down, \032 - left, \033 - right");
    DrawString(sdl->screen, sdl->screen->w / 2 - strlen(draw.text) * WIDTH_OF_SYMBOL / 2, 26, draw.text, sdl->charset);
    SDL_Rect forBar = {4, 4, SCREEN_WIDTH-8, HEIGHT_OF_INF_DISP};
    SDL_UpdateTexture(sdl->scrtex, NULL, sdl->screen->pixels, sdl->screen->pitch);
    SDL_RenderCopy(sdl->renderer, sdl->scrtex, &forBar, &forBar);
}

// draw health bar under player
void DrawHealthBarForPlayer(Sdl* sdl, Player player, Draw draw){
    double healthPerCent = 100*(double)player.health/(double)player.maxHealth/100;
    int barLength = LENGTH_OF_HEALTH_BAR;
    int x, y;
    if(barLength > player.width){
        x = player.x_coordinate - (barLength - player.width)/2 - sdl->camera.x;
    }else{
        x = player.x_coordinate + (player.width - barLength)/2 - sdl->camera.x;
    }
    y = player.y_coordinate - HEIGHT_OF_HEALTH_BAR - INDENT_TO_HEALTH_BAR - sdl->camera.y;
    if(y<0) y= 0;
    DrawRectangle(*sdl->screen, (unsigned int)x, (unsigned int)y, LENGTH_OF_HEALTH_BAR, HEIGHT_OF_HEALTH_BAR, draw.bialy, draw.czarny);
    DrawRectangle(*sdl->screen, (unsigned int)x+HEALTH_BAR_FRAME_THICKNESS, (unsigned int)y+HEALTH_BAR_FRAME_THICKNESS, (int)((LENGTH_OF_HEALTH_BAR-HEALTH_BAR_FRAME_THICKNESS*2)*healthPerCent), HEIGHT_OF_HEALTH_BAR-HEALTH_BAR_FRAME_THICKNESS*2, draw.czerwony, draw.czerwony);
    SDL_Rect forBar = {x, y, LENGTH_OF_HEALTH_BAR, HEIGHT_OF_HEALTH_BAR};
    SDL_UpdateTexture(sdl->scrtex, NULL, sdl->screen->pixels, sdl->screen->pitch);
    SDL_RenderCopy(sdl->renderer, sdl->scrtex, &forBar, &forBar);
}

// draw health bar under enemy
void DrawHealthBarForEnemy(Sdl* sdl, Enemy enemy, Draw draw){
    double healthPerCent = 100*(double)enemy.health/(double)enemy.maxHealth/100;
    int barLength = LENGTH_OF_HEALTH_BAR;
    int x, y;
    if(barLength > enemy.width){
        x = enemy.x_coordinate - (barLength - enemy.width)/2 - sdl->camera.x;
    }else{
        x = enemy.x_coordinate + (enemy.width - barLength)/2 - sdl->camera.x;
    }
    y = enemy.y_coordinate - HEIGHT_OF_HEALTH_BAR - INDENT_TO_HEALTH_BAR - sdl->camera.y;
    DrawRectangle(*sdl->screen, x, y, LENGTH_OF_HEALTH_BAR, HEIGHT_OF_HEALTH_BAR, draw.bialy, draw.czarny);
    DrawRectangle(*sdl->screen, x+HEALTH_BAR_FRAME_THICKNESS, y+HEALTH_BAR_FRAME_THICKNESS, (int)((LENGTH_OF_HEALTH_BAR-HEALTH_BAR_FRAME_THICKNESS*2)*healthPerCent), HEIGHT_OF_HEALTH_BAR-HEALTH_BAR_FRAME_THICKNESS*2, draw.czerwony, draw.czerwony);
    SDL_Rect forBar = {x, y, LENGTH_OF_HEALTH_BAR, HEIGHT_OF_HEALTH_BAR};
    SDL_UpdateTexture(sdl->scrtex, NULL, sdl->screen->pixels, sdl->screen->pitch);
    SDL_RenderCopy(sdl->renderer, sdl->scrtex, &forBar, &forBar);
}

// main function which display all elements during the game
void DrawGame(Sdl* sdl, Draw draw, Game game, Player player, Enemy enemy){
    SDL_RenderClear(sdl->renderer);
    DrawSky(sdl);
    DrawPlayer(sdl, player, game);
    DrawEnemy(sdl, enemy, game);
    DrawBulletForEnemy(sdl, enemy);
    DrawBulletForPlayer(sdl, player);
    if(enemy.health > 0) DrawHealthBarForEnemy(sdl, enemy, draw);
    if(player.health > 0)DrawHealthBarForPlayer(sdl, player, draw);
    DrawInfDisplay(sdl, draw, game);
    SDL_RenderPresent(sdl->renderer);
}

// draw moving icon in menu
void DrawIcon(Sdl* sdl, Icon icon){
    SDL_Rect source = {0, 0, PLAYER_WIDTH, PLAYER_HEIGHT};
    SDL_Rect dest;
    dest.x = icon.x_coordinate;
    dest.y = icon.y_coordinate;
    dest.w = PLAYER_WIDTH;
    dest.h = icon.height;
    SDL_RenderCopy(sdl->renderer, sdl->player, &source, &dest);
}

// draw given text in given coordinates
void DrawText(Sdl* sdl, Draw draw, char text[20], int x, int y, int w, int h){
    sprintf(draw.text, "%s", text);
    DrawString(sdl->screen, x, y, draw.text, sdl->charset);
    SDL_Rect dest = {x, y, w, h};
    SDL_UpdateTexture(sdl->scrtex, NULL, sdl->screen->pixels, sdl->screen->pitch);
    SDL_RenderCopy(sdl->renderer, sdl->scrtex, &dest, &dest);
}

// draw game menu
void DrawMenu(Sdl* sdl, Draw draw, Icon icon){
    SDL_Rect dest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_FillRect(sdl->screen, &dest, draw.czarny);
    SDL_RenderClear(sdl->renderer);
    DrawBackGround(sdl);
    DrawIcon(sdl, icon);
    char text[20];
    strcpy(text, "\"1\" Level 1");
    DrawText(sdl, draw, text, 280, 110, 90, 10);
    strcpy(text, "\"2\" Level 2");
    DrawText(sdl, draw, text, 280, 130, 90, 10);
    strcpy(text, "\"esc\" Quit");
    DrawText(sdl, draw, text, 290, 310, 80, 10);
    SDL_RenderPresent(sdl->renderer);
}

// draw special menu when player lose
void DrawLoseMenu(Sdl* sdl, Draw draw){
    char text[20];
    SDL_Rect dest = {X_INDENT_FOR_MENU, Y_INDENT_FOR_MENU, SCREEN_WIDTH-X_INDENT_FOR_MENU*2, SCREEN_HEIGHT-Y_INDENT_FOR_MENU*2};
    SDL_FillRect(sdl->screen, &dest, draw.czarny);
    SDL_UpdateTexture(sdl->scrtex, NULL, sdl->screen->pixels, sdl->screen->pitch);
    SDL_RenderCopy(sdl->renderer, sdl->scrtex, &dest, &dest);
    strcpy(text, "Game Over");
    DrawText(sdl, draw, text, 280, 110, 90, 10);
    strcpy(text, "\"T\" Try again");
    DrawText(sdl, draw, text, 110, SCREEN_HEIGHT - 200, 110, 10);
    strcpy(text, "\"esc\" To menu");
    DrawText(sdl, draw, text, SCREEN_WIDTH - 230, SCREEN_HEIGHT - 200, 110, 10);
    SDL_RenderPresent(sdl->renderer);
}

// draw special menu when player win
void DrawWinMenu(Sdl* sdl, Draw draw){
    char text[20];
    SDL_Rect dest = {X_INDENT_FOR_MENU, Y_INDENT_FOR_MENU, SCREEN_WIDTH-X_INDENT_FOR_MENU*2, SCREEN_HEIGHT-Y_INDENT_FOR_MENU*2};
    SDL_FillRect(sdl->screen, &dest, draw.czarny);
    SDL_UpdateTexture(sdl->scrtex, NULL, sdl->screen->pixels, sdl->screen->pitch);
    SDL_RenderCopy(sdl->renderer, sdl->scrtex, &dest, &dest);
    strcpy(text, "Win");
    DrawText(sdl, draw, text, 290, 110, 90, 10);
    strcpy(text, "\"N\" Next Level");
    DrawText(sdl, draw, text, 110, SCREEN_HEIGHT - 200, 110, 10);
    strcpy(text, "\"esc\" To menu");
    DrawText(sdl, draw, text, SCREEN_WIDTH - 250, SCREEN_HEIGHT - 200, 110, 10);
    SDL_RenderPresent(sdl->renderer);
}