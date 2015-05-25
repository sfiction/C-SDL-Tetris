#ifndef _TETRIS_GAME_H
#define _TETRIS_GAME_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"

typedef Uint32 ttsColor;

typedef Uint16 ttsShape;

/*
 *	12	13	14	15
 *	8	9	10	11
 *	4	5	6	7
 *	0	1	2	3
 */
#define SHAPE_TYPE 6
#define SHAPE_ROTATE 4
#define SHAPE_N (SHAPE_TYPE * SHAPE_ROTATE)

static const constTtsShape[SHAPE_TYPE][SHAPE_ROTATE] = {
		{0x0033, 0x0033, 0x0033, 0x0033},
		{0x1111, 0x000f, 0x1111, 0x000f},
		{0x0113, 0x0047, 0x0322, 0x0071},
		{0x0223, 0x0074, 0x0311, 0x0017},
		{0x0132, 0x0063, 0x0132, 0x0063},
		{0x0231, 0x0036, 0x0231, 0x0036}};

typedef struct{
	Uint32 x, y;
	Uint32 color;
	Uint8 id;
}ttsItem;

extern Uint32 score;
extern Uint32 clearedLines;

extern Uint32 map[ROW_N];
extern Uint32 mapColor[ROW_N][COL_N];

extern ttsItem fall;

inline Uint32 getShapeDigit(ttsShape s, Uint32 i, Uint32 j);
inline ttsShape getConstTtsShape(Uint8 id);

void initGame();

int inRange(int x, int y);
inline Uint32 isOverUpSide(ttsItem *t);
inline Uint32 isOverDownSide(ttsItem *t);
inline Uint32 isOverLeftSide(ttsItem *t);
inline Uint32 isOverRightSide(ttsItem *t);
Uint32 isLegal(ttsItem *t);

ttsItem getTtsItem();
ttsItem getLegalTtsItem();

#endif
