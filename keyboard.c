#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"
#include "game.h"

void keyboard(SDL_Event *e){
	SDL_Keycode key;

	if (e->type == SDL_QUIT)
		gQuit = 1;
	else if (e->type == SDL_KEYDOWN){
		if ((key = e->key.keysym.sym) == SDLK_ESCAPE)
			gQuit = 1;
		else if (key == SDLK_SPACE)
			gPause ^= 1;
		else if (!gPause){
			switch (key){
			case SDLK_UP:
				//todo
				break;
			case SDLK_DOWN:
				++fall.x;
				if (!isLegal(&fall))
					--fall.x;
				break;
			case SDLK_LEFT:
				--fall.y;
				if (!isLegal(&fall))
					++fall.y;
				break;
			case SDLK_RIGHT:
				++fall.y;
				if (!isLegal(&fall))
					--fall.y;
				break;
			default:
				break;
			}
		}
	}
}
