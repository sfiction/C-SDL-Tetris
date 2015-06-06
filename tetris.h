/*
 * XXX_XXX	#define
 * XXX_Xxx	enum
 * xxxXxx	variable or struct
 */

#ifndef _TETRIS_TETRIS_H
#define _TETRIS_TETRIS_H

#include <SDL.h>
#include <SDL_ttf.h>

/*
 * window:
 * game:		window
 * display:		window	game
 * timer:		window	game	display
 * keyboard:	game	timer
 */
#include "window.h"
#include "game.h"
#include "display.h"
#include "timer.h"
#include "keyboard.h"

void init();
void close();

#endif
