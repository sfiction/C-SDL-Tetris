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
	if (gameStatus == GAME_Active){
		if (!roundCnt)
			gameUpdate();

		roundCnt = (roundCnt + 1) % (TIME_ROUND / gameSpeed);
	}

	display();

	return interval;
}
