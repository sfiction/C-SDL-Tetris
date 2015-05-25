#ifndef _TETRIS_TIMER_H
#define _TETRIS_TIMER_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"
#include "display.h"
#include "game.h"

static const Uint32 roundCntMod  = TIME_ROUND / TIME_SPEED;
extern Uint32 roundCnt;

void initTimer();

Uint32 timerMain(Uint32 interval, void *param);

#endif
