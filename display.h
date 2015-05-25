#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"
#include "game.h"

#define MAXSL 200

void initDisplay();

void displayMessage(SDL_Renderer *Renderer, char *message, int x0, int y0, const SDL_Color *color);
void displayInformation();
void display();

#endif
