#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>

#include "window.h"
#include "game.h"
#include "display.h"

void displaySingleLineMessage(SDL_Renderer *Renderer, char *message, Uint32 x0, Uint32 y0, const SDL_Color *color){
	SDL_Surface *word_S = TTF_RenderText_Solid(Courier_New, message, *color);
	SDL_Texture *word_T = SDL_CreateTextureFromSurface(gRenderer, word_S);

	SDL_Rect temp = {x0, y0, word_S->w, word_S->h};
	SDL_RenderCopy(Renderer, word_T, NULL, &temp);

	SDL_FreeSurface(word_S);
	SDL_DestroyTexture(word_T);
}

void displayMessage(SDL_Renderer *Renderer, char *message, Uint32 x0, Uint32 y0, Uint32 fontSize, const SDL_Color *color){
	static char str[MAXSL];
	static int cntLine;
	int i = 0, j;
	
	for (cntLine = 0; message[i]; ++cntLine){
		for (j = 0; message[i] != '\n' && message[i] != '\0'; ++i, ++j)
			str[j] = message[i];
		i += message[i] == '\n';
		str[j] = '\0';
		if (j)
			displaySingleLineMessage(gRenderer, str, x0, y0 + cntLine * fontSize, color);
	}
}

void displayScoreBoard(){
	static char str[MAXSL];
	char *pos = str;

//	sprintf(str, "Time Passed:\n%12.3lfs", SDL_GetTicks() / 1000.0);
	pos += sprintf(pos, "Speed:\n%10d\n", gameSpeed);
	pos += sprintf(pos, "Score:\n%10d\n", score);
	pos += sprintf(pos, "Cleared lines:\n%10d\n", clearedLines);
	displayMessage(gRenderer, str, INFO_POS_X, INFO_POS_Y, FONT_SIZE, &COLOR_WHITE);
}

void displayHint(){
	static char str[MAXSL];
	char *pos = str;

	switch (gameStatus){
	case GAME_Active:
		pos += sprintf(pos, "Active\n");
		break;
	case GAME_Pause:
		pos += sprintf(pos, "Pause\n");
		break;
	case GAME_Start:
		pos += sprintf(pos, "New Game\n");
		break;
	case GAME_End:
		pos += sprintf(pos, "Finished\n");
		break;
	default:
		str[0] = '\0';
	}

	pos += sprintf(pos, " \n");
	pos += sprintf(pos, "A/F\nUp/Down speed\n");
	pos += sprintf(pos, "R\nReset\n");
	pos += sprintf(pos, "P\nPause/Continue\n");

	displayMessage(gRenderer, str, HINT_POS_X, HINT_POS_Y + 3 * FONT_SIZE, FONT_SIZE, &COLOR_WHITE);
}

void drawSmallRect(Uint32 x0, Uint32 y0, Uint32 row, Uint32 col, ttsColor color){
	SDL_SetRenderDrawColor(gRenderer, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, 0xff);
	SDL_Rect rect = {x0 + col * COL_SIZE + 1, y0 + row * ROW_SIZE + 1, COL_SIZE - 2, ROW_SIZE - 2};
	SDL_RenderFillRect(gRenderer, &rect);
}

void drawShape(Uint32 x0, Uint32 y0, ttsItem *t){
	int i, j;
	for (i = 0; i < 4; ++i)
		for (j = 0; j < 4; ++j)
			if (getShapeBit(t->id, i, j) && inRange(t->x - i, t->y + j))
				drawSmallRect(x0, y0, t->x - i, t->y + j, t->color);
}

void display(){
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
	SDL_RenderClear(gRenderer);

	int i, j;

	//play
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Rect playFrame = {PLAY_POS_X, PLAY_POS_Y, PLAY_WIDTH, PLAY_HEIGHT};
	SDL_RenderDrawRect(gRenderer, &playFrame);
	for (i = 0; i < PLAY_ROW_N; ++i)
		for (j = 0; j < PLAY_COL_N; ++j)
			drawSmallRect(PLAY_POS_X, PLAY_POS_Y, i, j, map[i][j] ? mapColor[i][j] : (i << 19 | j << 4));
	drawShape(PLAY_POS_X, PLAY_POS_Y, &fallItem);


	//next shape
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_Rect nextFrame = {NEXT_POS_X, NEXT_POS_Y, NEXT_WIDTH, NEXT_HEIGHT};
	SDL_RenderDrawRect(gRenderer, &nextFrame);
	drawShape(NEXT_POS_X, NEXT_POS_Y, &nextItem);

	//informations
	displayScoreBoard();
	displayHint();

	SDL_RenderPresent(gRenderer);
}
