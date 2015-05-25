#ifndef _CENTER_H
#define _CENTER_H

#include <SDL.h>
#include <SDL_ttf.h>

//fonts
#define FONT_PATH_COURIER_NEW "src\\fonts\\cour.ttf"
#define FONT_SIZE 14

//time control
//TIME_SPEED rows / s
#define TIME_SPEED 2
#define TIME_ROUND 50
#define TIME_PERIOD (1000 / TIME_ROUND)

#define SPACE_SIZE 25

//play
#define SIDE_LENGTH 25
#define COL_SIZE SIDE_LENGTH
#define ROW_SIZE SIDE_LENGTH
#define COL_N 10
#define ROW_N 20
#define PLAY_WIDTH (COL_N * COL_SIZE)
#define PLAY_HEIGHT (ROW_N * ROW_SIZE)
#define PLAY_POS_X SPACE_SIZE
#define PLAY_POS_Y SPACE_SIZE

//next shape
#define NEXT_WIDTH (SIDE_LENGTH << 2)
#define NEXT_HEIGHT (NEXT_WIDTH)
#define NEXT_POS_X (PLAY_POS_X + PLAY_WIDTH + SPACE_SIZE)
#define NEXT_POS_Y PLAY_POS_Y

//information
#define INFO_POS_X NEXT_POS_X
#define INFO_POS_Y (NEXT_POS_Y + NEXT_HEIGHT + SPACE_SIZE)

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

extern Uint32 gQuit, gPause;

#endif
