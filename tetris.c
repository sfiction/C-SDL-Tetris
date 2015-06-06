#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"
#include "game.h"
#include "display.h"
#include "timer.h"
#include "keyboard.h"
#include "tetris.h"

void init(){
	initWindow();
	initGame(GAME_SPEED_START);
	initTimer();
}

void close(){
	closeWindow();
}
