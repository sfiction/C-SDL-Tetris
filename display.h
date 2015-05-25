#ifndef _TETRIS_DISPLAY_H
#define _TETRIS_DISPLAY_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"
#include "game.h"

#define MAXSL 200

void initDisplay();

void displayMessage(SDL_Renderer *Renderer, char *message, int x0, int y0, const SDL_Color *color);
void displayInformation();
void drawSmallRect(Uint32 row, Uint32 col, Uint32 color);
void display();

#endif
