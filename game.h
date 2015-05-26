#ifndef _TETRIS_GAME_H
#define _TETRIS_GAME_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "window.h"

typedef Uint32 ttsColor;

typedef Uint32 ttsShape;

/*
 * 0 - 15	show the shpae
 * 16 - 19	width
 * 20 - 23	height
 *	12	13	14	15
 *	8	9	10	11
 *	4	5	6	7
 *	0	1	2	3
 */
#define SHAPE_SIZE 4
#define SHAPE_TYPE 7
#define SHAPE_ROTATE 4
#define SHAPE_N (SHAPE_TYPE * SHAPE_ROTATE)

static const constShape[SHAPE_TYPE][SHAPE_ROTATE] = {
		{0x220033, 0x220033, 0x220033, 0x220033},
		{0x411111, 0x14000f, 0x411111, 0x14000f},
		{0x320113, 0x230047, 0x320322, 0x230071},
		{0x320223, 0x230074, 0x320311, 0x230017},
		{0x320132, 0x230063, 0x320132, 0x230063},
		{0x320231, 0x230036, 0x320231, 0x230036},
		{0x320232, 0x230072, 0x320131, 0x230027}};

static const constShapeColor[SHAPE_TYPE] = {0x0000ff, 0x00ff00, 0x00ffff, 0xff0000, 0xff00ff, 0xffff00, 0xffffff};

typedef struct{
	Sint32 x, y;
	Uint32 color;
	Uint32 id;
}ttsItem;

extern Uint32 score;
extern Uint32 clearedLines;

extern Uint8 map[ROW_N][COL_N];
extern ttsColor mapColor[ROW_N][COL_N];

extern ttsItem fall;

inline ttsShape getConstShape(Uint32 id);
inline Uint32 getShapeBit(Uint32 id, Uint32 i, Uint32 j);
inline Uint32 getShapeWidth(Uint32 id);
inline Uint32 getShapeHeight(Uint32 id);
inline Uint32 getShapeColor(Uint32 id);
inline Uint32 getRotatedShape(Uint32 id);

int inRange(int x, int y);
inline Uint32 isOverUpSide(ttsItem *t);
inline Uint32 isOverDownSide(ttsItem *t);
inline Uint32 isOverLeftSide(ttsItem *t);
inline Uint32 isOverRightSide(ttsItem *t);
inline Uint32 isOverSide(ttsItem *t);

Uint32 isLegal(ttsItem *t);

ttsItem getItem();
ttsItem getLegalItem();

Uint32 rotateClock(ttsItem *t);
Uint32 rotateAnti(ttsItem *t);
Uint32 moveUp(ttsItem *t);
Uint32 moveDown(ttsItem *t);
Uint32 moveLeft(ttsItem *t);
Uint32 moveRight(ttsItem *t);
void moveBottom(ttsItem *t);

Uint32 isFull();
Uint32 clearSingleLine();
void clearLines();

void addItemToMap(ttsItem *t);

void gameUpdate();
void initGame();

#endif
