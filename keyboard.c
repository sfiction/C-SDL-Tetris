#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"
#include "game.h"
#include "timer.h"

void keyboard(SDL_Event *e){
	SDL_Keycode key;

	if (e->type == SDL_QUIT)
		gQuit = 1;
	else if (e->type == SDL_KEYDOWN){
		if ((key = e->key.keysym.sym) == SDLK_ESCAPE)
			gQuit = 1;
		else if (key == SDLK_p){
			switch (gameStatus){
			case GAME_Active:
				gameStatus = GAME_Pause;
				break;
			case GAME_Pause:
			case GAME_Start:
				gameStatus = GAME_Active;
				break;
			case GAME_End:
				initGame();
				gameStatus = GAME_Active;
				break;
			default:
				break;
			}
		}
		else if (key == SDLK_r){
			initGame();
			gameStatus = GAME_Active;
		}
		else if (gameStatus == GAME_Active){
			switch (key){
			case SDLK_SPACE:
				moveBottom(&fallItem);
				gameUpdate();
				roundCnt = 1;
				break;
			case SDLK_UP:
				rotateClock(&fallItem);
				break;
			case SDLK_DOWN:
				gameUpdate();
				roundCnt = 1;
				break;
			case SDLK_LEFT:
				moveLeft(&fallItem);
				break;
			case SDLK_RIGHT:
				moveRight(&fallItem);
				break;
			default:
				break;
			}
		}
	}
}
