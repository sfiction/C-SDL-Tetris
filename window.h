#ifndef _TETRIS_CENTER_H
#define _TETRIS_CENTER_H

#include <SDL.h>
#include <SDL_ttf.h>

//fonts
#define FONT_PATH_COURIER_NEW "src\\fonts\\cour.ttf"
#define FONT_SIZE 14

#define TIME_ROUND 60
#define TIME_PERIOD (1000 / TIME_ROUND)

#define SPACE_SIZE 25

//shape
#define SHAPE_SIZE 4
#define SIDE_LENGTH 25
#define COL_SIZE SIDE_LENGTH
#define ROW_SIZE SIDE_LENGTH

//play
#define PLAY_COL_N 10
#define PLAY_ROW_N 20
#define PLAY_WIDTH (PLAY_COL_N * COL_SIZE)
#define PLAY_HEIGHT (PLAY_ROW_N * ROW_SIZE)
#define PLAY_POS_X SPACE_SIZE
#define PLAY_POS_Y SPACE_SIZE

//next shape
#define NEXT_COL_N SHAPE_SIZE
#define NEXT_ROW_N SHAPE_SIZE
#define NEXT_WIDTH (NEXT_COL_N * COL_SIZE)
#define NEXT_HEIGHT (NEXT_ROW_N * ROW_SIZE)
#define NEXT_POS_X (PLAY_POS_X + PLAY_WIDTH + SPACE_SIZE)
#define NEXT_POS_Y PLAY_POS_Y

//score board
#define INFO_ROW_N 6
#define INFO_ROW_SIZE FONT_SIZE
#define INFO_HEIGHT (INFO_ROW_N * INFO_ROW_SIZE)
#define INFO_POS_X NEXT_POS_X
#define INFO_POS_Y (NEXT_POS_Y + NEXT_HEIGHT + SPACE_SIZE)

//hints
#define HINT_ROW_N 6
#define HINT_ROW_SIZE FONT_SIZE
#define HINT_POS_X NEXT_POS_X
#define HINT_POS_Y (INFO_POS_Y + INFO_HEIGHT + SPACE_SIZE)

//window
#define TITLE "Tetris"
#define SCREEN_POS_X 100
#define SCREEN_POS_Y 100
#define SCREEN_WIDTH (NEXT_POS_X + NEXT_WIDTH + SPACE_SIZE)
#define SCREEN_HEIGHT (PLAY_POS_Y + PLAY_HEIGHT + SPACE_SIZE)

static const SDL_Color COLOR_WHITE = {0xff, 0xff, 0xff};
static const SDL_Color COLOR_BLACK = {0x00, 0x00, 0x00};
static const SDL_Color COLOR_RED = {0xff, 0x00, 0x00};
static const SDL_Color COLOR_GREEN = {0x00, 0xff, 0x00};
static const SDL_Color COLOR_BLUE = {0x00, 0x00, 0xff};

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

extern TTF_Font *Courier_New;

extern Uint32 gQuit;

#endif
