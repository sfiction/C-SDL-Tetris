#ifndef _TETRIS_TIMER_H
#define _TETRIS_TIMER_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"
#include "game.h"
#include "display.h"

extern Uint32 roundCnt;

void initTimer();

Uint32 timerMain(Uint32 interval, void *param);

#endif
