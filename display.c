#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>

#include "window.h"
#include "game.h"
#include "display.h"

void initDisplay(){
}

void displayMessage(SDL_Renderer *Renderer, char *message, int x0, int y0, const SDL_Color *color){
	SDL_Surface *word_S = TTF_RenderText_Solid(Courier_New, message, *color);
	SDL_Texture *word_T = SDL_CreateTextureFromSurface(gRenderer, word_S);

	SDL_Rect temp = {x0, y0, word_S->w, word_S->h};
	SDL_RenderCopy(Renderer, word_T, NULL, &temp);

	SDL_FreeSurface(word_S);
	SDL_DestroyTexture(word_T);
}

void displayInformation(){
	static int cntLine;
	static char str[MAXSL];

	cntLine = 0;

	displayMessage(gRenderer, "Time Passed:", INFO_POS_X, INFO_POS_Y + cntLine++ * FONT_SIZE, &COLOR_WHITE);
	sprintf(str, "%12.3lfs", SDL_GetTicks() / 1000.0);
	displayMessage(gRenderer, str, INFO_POS_X, INFO_POS_Y + cntLine++ * FONT_SIZE, &COLOR_WHITE);
	displayMessage(gRenderer, "Score:", INFO_POS_X, INFO_POS_Y + cntLine++ * FONT_SIZE, &COLOR_WHITE);
	sprintf(str, "%12d", score);
	displayMessage(gRenderer, str, INFO_POS_X, INFO_POS_Y + cntLine++ * FONT_SIZE, &COLOR_WHITE);
	displayMessage(gRenderer, "Cleared Lines:", INFO_POS_X, INFO_POS_Y + cntLine++ * FONT_SIZE, &COLOR_WHITE);
	sprintf(str, "%12d", clearedLines);
	displayMessage(gRenderer, str, INFO_POS_X, INFO_POS_Y + cntLine++ * FONT_SIZE, &COLOR_WHITE);
}

void display(){
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(gRenderer);

	//play part
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Rect playFrame = {PLAY_POS_X, PLAY_POS_Y, PLAY_WIDTH, PLAY_HEIGHT};
	SDL_RenderDrawRect(gRenderer, &playFrame);

	//shape
	
	//next shape
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Rect nextFrame = {NEXT_POS_X, NEXT_POS_Y, NEXT_WIDTH, NEXT_HEIGHT};
	SDL_RenderDrawRect(gRenderer, &nextFrame);

	//infomation
	displayInformation();

	SDL_RenderPresent(gRenderer);
}
