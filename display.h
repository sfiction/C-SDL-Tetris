#ifndef _TETRIS_DISPLAY_H
#define _TETRIS_DISPLAY_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"
#include "game.h"

#define MAXSL 200

//single line
void displaySingleLineMessage(SDL_Renderer *Renderer, char *message, Uint32 x0, Uint32 y0, const SDL_Color *color);
//multiple lines
void displayMessage(SDL_Renderer *Renderer, char *message, Uint32 x0, Uint32 y0, Uint32 fontSize, const SDL_Color *color);

void displayScoreBoard();
void displayHint();

void drawSmallRect(Uint32 POS_X, Uint32 POS_Y, Uint32 row, Uint32 col, ttsColor color);
void drawShape(Uint32 POS_X, Uint32 POS_Y, ttsItem *t);

void display();

#endif
