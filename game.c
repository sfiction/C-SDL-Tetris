#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"

Uint32 score;
Uint32 clearedLines;

void initGame(){
	score = 0;
	clearedLines = 0;
}
