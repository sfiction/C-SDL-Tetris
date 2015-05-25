#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"
#include "display.h"
#include "game.h"
#include "timer.h"

Uint32 roundCnt;

void initTimer(){
	roundCnt = 0;
}

Uint32 timerMain(Uint32 interval, void *param){
	if (gPause)
		return;

	if (!roundCnt){
		++fall.x;
		if (fall.x == ROW_N)
			fall = getLegalTtsItem();
	}

	roundCnt = (roundCnt + 1) % roundCntMod;

	display();

	return interval;
}
