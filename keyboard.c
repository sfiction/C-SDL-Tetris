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
		else if (key == SDLK_p)
			gPause ^= 1;
		else if (!gPause){
			switch (key){
			case SDLK_SPACE:
				moveBottom(&fall);
				break;
			case SDLK_UP:
				rotateAnti(&fall);
				break;
			case SDLK_DOWN:
				moveDown(&fall);
				break;
			case SDLK_LEFT:
				moveLeft(&fall);
				break;
			case SDLK_RIGHT:
				moveRight(&fall);
				break;
			default:
				break;
			}
		}
	}
}
