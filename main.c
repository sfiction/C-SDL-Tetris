#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>

#include "tetris.h"

int main(int argc, char *argv[]){
	init();

	Uint32 timerIDMain = SDL_AddTimer(TIME_PERIOD, timerMain, NULL);
	
	SDL_Event e;
	while (!gQuit){
		SDL_WaitEvent(&e);
		keyboard(&e);
	}
	
	SDL_RemoveTimer(timerIDMain);
	
	close();

	return 0;
}
