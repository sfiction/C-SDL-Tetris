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
 *
 *	12	13	14	15
 *	8	9	10	11
 *	4	5	6	7
 *	0	1	2	3
 */
#define SHAPE_TYPE 7
#define SHAPE_ROTATE 4
#define SHAPE_N (SHAPE_TYPE * SHAPE_ROTATE)

static const ttsShape constShape[SHAPE_TYPE][SHAPE_ROTATE] = {
		{0x220033, 0x220033, 0x220033, 0x220033},
		{0x411111, 0x14000f, 0x411111, 0x14000f},
		{0x320113, 0x230047, 0x320322, 0x230071},
		{0x320223, 0x230074, 0x320311, 0x230017},
		{0x320132, 0x230063, 0x320132, 0x230063},
		{0x320231, 0x230036, 0x320231, 0x230036},
		{0x320232, 0x230072, 0x320131, 0x230027}};

static const ttsColor constShapeColor[SHAPE_TYPE] = {0x0000ff, 0x00ff00, 0x00ffff, 0xff0000, 0xff00ff, 0xffff00, 0xffffff};

typedef struct{
	Sint32 x, y;
	Uint32 color;
	Uint32 id;
}ttsItem;

//game status
enum{
	GAME_Active = 0,
	GAME_Pause = 1,
	GAME_Start = 2,
	GAME_End = 3
};

//speed control
#define GAME_SPEED_START 2
#define GAME_SPEED_LOWER 1
#define GAME_SPEED_UPPER 20

extern Uint32 gameSpeed;
extern Uint32 gameStatus;

extern Uint32 score;
extern Uint32 clearedLines;

//play map
extern Uint8 map[PLAY_ROW_N][PLAY_COL_N];
extern ttsColor mapColor[PLAY_ROW_N][PLAY_COL_N];

extern ttsItem fallItem, nextItem;

inline ttsShape getConstShape(Uint32 id);
inline Uint32 getShapeBit(Uint32 id, Uint32 i, Uint32 j);
inline Uint32 getShapeWidth(Uint32 id);
inline Uint32 getShapeHeight(Uint32 id);
inline Uint32 getShapeColor(Uint32 id);
inline Uint32 getRotatedShape(Uint32 id);

inline Uint32 inRange(int x, int y);
inline Uint32 isOverUpSide(ttsItem *t);
inline Uint32 isOverDownSide(ttsItem *t);
inline Uint32 isOverLeftSide(ttsItem *t);
inline Uint32 isOverRightSide(ttsItem *t);
inline Uint32 isOverSide(ttsItem *t);
Uint32 isLegal(ttsItem *t);

Uint32 rotateClock(ttsItem *t);
Uint32 rotateAnti(ttsItem *t);
Uint32 moveUp(ttsItem *t);
Uint32 moveDown(ttsItem *t);
Uint32 moveLeft(ttsItem *t);
Uint32 moveRight(ttsItem *t);
void moveBottom(ttsItem *t);

Uint32 isFull(int i);//check a single line is full or not
Uint32 clearSingleLine();
void clearLines();

ttsItem getItem();
ttsItem getLegalItem();
void getNextItem();
void nextToFall();
Uint32 addItemToMap(ttsItem *t);//draw the item on the map, the item will cover the map if there are conflicts

Uint32 setSpeed(Uint32 newSpeed);//change game speed

void gameUpdate();

void initGame(Uint32 speed);

#endif
