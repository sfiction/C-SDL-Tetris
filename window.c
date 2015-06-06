#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"

SDL_Window *gWindow;
SDL_Renderer *gRenderer;

TTF_Font *Courier_New;

Uint32 gQuit;

void initWindow(){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	gWindow = SDL_CreateWindow(TITLE, SCREEN_POS_X, SCREEN_POS_Y, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(gRenderer);
	SDL_RenderPresent(gRenderer);

	TTF_Init();
	Courier_New = TTF_OpenFont(FONT_PATH_COURIER_NEW, FONT_SIZE);

	gQuit = 0;
}

void closeWindow(){
	TTF_CloseFont(Courier_New);
	Courier_New = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	TTF_Quit();
	TTF_Quit();
}
