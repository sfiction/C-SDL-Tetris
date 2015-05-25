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

void drawSmallRect(Uint32 row, Uint32 col, ttsColor color){
	SDL_SetRenderDrawColor(gRenderer, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, 0xff);
	SDL_Rect rect = {PLAY_POS_X + col * COL_SIZE + 1, PLAY_POS_Y + row * ROW_SIZE + 1, COL_SIZE - 2, ROW_SIZE - 2};
	SDL_RenderFillRect(gRenderer, &rect);
}

void display(){
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(gRenderer);

	int i, j;

	//play frame
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Rect playFrame = {PLAY_POS_X, PLAY_POS_Y, PLAY_WIDTH, PLAY_HEIGHT};
	SDL_RenderDrawRect(gRenderer, &playFrame);

	//play map
	for (i = 0; i < ROW_N; ++i)
		for (j = 0; j < COL_N; ++j)
			if (map[i] & (1 << j))
				drawSmallRect(i, j, mapColor[i][j]);

	//shape
	ttsShape fs = getConstTtsShape(fall.id);
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j){
//			printf("%d %d %x %x %d\n", i, j, fs, 1 << (i << 2 | j), fs & (1 << (i << 2 | j)));
			if (getShapeDigit(fs, i, j) && inRange(fall.x - i, fall.y + j))
				drawSmallRect(fall.x - i, fall.y + j, fall.color);
		}

	//next shape
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Rect nextFrame = {NEXT_POS_X, NEXT_POS_Y, NEXT_WIDTH, NEXT_HEIGHT};
	SDL_RenderDrawRect(gRenderer, &nextFrame);

	//infomation
	displayInformation();

	SDL_RenderPresent(gRenderer);
}
