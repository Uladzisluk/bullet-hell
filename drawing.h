//
// Created by Uladzislau Lukashevich on 09/01/2022.
//

#ifndef BULLET_HELL_DRAWING_H
#define BULLET_HELL_DRAWING_H

#include <SDL.h>
#include "structs.h"

void initDraw(Draw* draw, SDL_Surface* screen);
void DrawString(SDL_Surface* screen, int x, int y, const char *text, SDL_Surface* charset);
void DrawPlayer(Sdl* sdl, Player player, Game game);
void DrawEnemy(Sdl* sdl, Enemy enemy, Game game);
void DrawBulletForEnemy(Sdl* sdl, Enemy enemy);
void DrawBulletForPlayer(Sdl* sdl, Player player);
void DrawPixel(SDL_Surface surface, int x, int y, Uint32 color);
void DrawLine(SDL_Surface screen, int x, int y, int l, int dx, int dy, Uint32 color);
void DrawRectangle(SDL_Surface screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
void DrawSky(Sdl* sdl);
void DrawBackGround(Sdl* sdl);
void DrawInfDisplay(Sdl* sdl, Draw draw, Game game);
void DrawHealthBarForPlayer(Sdl* sdl, Player player, Draw draw);
void DrawHealthBarForEnemy(Sdl* sdl, Enemy enemy, Draw draw);
void DrawGame(Sdl* sdl, Draw draw, Game game, Player player, Enemy enemy);
void DrawIcon(Sdl* sdl, Icon icon);
void DrawText(Sdl* sdl, Draw draw, char* text, int x, int y, int w, int h);
void DrawMenu(Sdl* sdl, Draw draw, Icon icon);
void DrawLoseMenu(Sdl* sdl, Draw draw);
void DrawWinMenu(Sdl* sdl, Draw draw);

#endif //BULLET_HELL_DRAWING_H
