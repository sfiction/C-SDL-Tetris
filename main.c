#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>

#include "tetris.h"

int main(int argc, char *argv[]){
	init();

	Uint32 timerIDMain = SDL_AddTimer(TIME_PERIOD, timerMain, NULL);
	
	SDL_Event e;
	Uint32 key;
	while (!gQuit){
		SDL_WaitEvent(&e);
		if (e.type == SDL_QUIT)
			gQuit = 1;
		else if (e.type == SDL_KEYDOWN){
			if ((key = e.key.keysym.sym) == SDLK_ESCAPE)
				gQuit = 1;
			else if (key == SDLK_SPACE)
				gPause ^= 1;
//			else if (!pause && 0 <= key && key)
		}
	}
	
	SDL_RemoveTimer(timerIDMain);
	
	close();

	return 0;
}
