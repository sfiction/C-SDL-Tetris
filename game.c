#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "window.h"
#include "game.h"

Uint32 gameStatus;

Uint32 score;
Uint32 clearedLines;

Uint8 map[PLAY_ROW_N][PLAY_COL_N];
ttsColor mapColor[PLAY_ROW_N][PLAY_COL_N];

ttsItem fallItem, nextItem;

inline ttsShape getConstShape(Uint32 id){
	return constShape[id / SHAPE_ROTATE][id % SHAPE_ROTATE];
}

inline Uint32 getShapeBit(Uint32 id, Uint32 i, Uint32 j){
	return !!(getConstShape(id) & (1 << (i << 2 | j)));
}

inline Uint32 getShapeWidth(Uint32 id){
	return getConstShape(id) >> 16 & 0xf;
}

inline Uint32 getShapeHeight(Uint32 id){
	return getConstShape(id) >> 20 & 0xf;
}

inline Uint32 getShapeColor(Uint32 id){
	return constShapeColor[id / SHAPE_ROTATE];
}

inline Uint32 getRotatedClockShape(Uint32 id){
	return id / SHAPE_ROTATE * SHAPE_ROTATE	+ (id - 1 + SHAPE_ROTATE) % SHAPE_ROTATE;
}

inline Uint32 getRotatedAntiShape(Uint32 id){
	return id / SHAPE_ROTATE * SHAPE_ROTATE	+ (id + 1) % SHAPE_ROTATE;
}

int inRange(int x, int y){
	return 0 <= x && x < PLAY_ROW_N && 0 <= y && y < PLAY_COL_N;
}

inline Uint32 isOverUpSide(ttsItem *t){
	return t->x < 0;
}

inline Uint32 isOverDownSide(ttsItem *t){
	return t->x >= PLAY_ROW_N;
}

inline Uint32 isOverLeftSide(ttsItem *t){
	return t->y < 0;
}

inline Uint32 isOverRightSide(ttsItem *t){
	return t->y + getShapeWidth(t->id) - 1 >= PLAY_COL_N;
}

inline Uint32 isOverSide(ttsItem *t){
	return isOverUpSide(t) || isOverDownSide(t)
		|| isOverLeftSide(t) || isOverRightSide(t);
}

Uint32 isLegal(ttsItem *t){
	if (isOverSide(t))
		return 0;
	int i, j, x, y;
	for (i = 0; i < SHAPE_SIZE; ++i)
		for (j = 0; j < SHAPE_SIZE; ++j)
			if (getShapeBit(t->id, i, j)){
				x = t->x - i;
				y = t->y + j;
				if (inRange(x, y) && map[x][y])
					return 0;
			}
	return 1;
}

ttsItem getItem(){
	ttsItem t;
	t.id = rand() % SHAPE_N;
	t.x = 0;
	t.y = rand() % (PLAY_COL_N - getShapeWidth(t.id) + 1) + (getShapeWidth(t.id) - 1);
	t.color = getShapeColor(t.id);
	return t;
}

ttsItem getLegalItem(){
	ttsItem t;
	do{
		t = getItem();
	}while (!isLegal(&t));
	return t;
}

Uint32 rotateClock(ttsItem *t){
	t->id = getRotatedClockShape(t->id);
	if (isLegal(t))
		return 1;
	t->id = getRotatedAntiShape(t->id);
	return 0;
}

Uint32 rotateAnti(ttsItem *t){
	t->id = getRotatedAntiShape(t->id);
	if (isLegal(t))
		return 1;
	t->id = getRotatedClockShape(t->id);
	return 0;
}

Uint32 moveUp(ttsItem *t){
	--t->x;
	if (isLegal(t))
		return 1;
	++t->x;
	return 0;
}

Uint32 moveDown(ttsItem *t){
	++t->x;
	if (isLegal(t))
		return 1;
	--t->x;
	return 0;
}

Uint32 moveLeft(ttsItem *t){
	--t->y;
	if (isLegal(t))
		return 1;
	++t->y;
	return 0;
}

Uint32 moveRight(ttsItem *t){
	++t->y;
	if (isLegal(t))
		return 1;
	--t->y;
	return 0;
}

void moveBottom(ttsItem *t){
	while (moveDown(t));
}

Uint32 isFull(int i){
	int j;
	for (j = 0; j < PLAY_COL_N; ++j)
		if (!map[i][j])
			return 0;
	return 1;
}

Uint32 clearSingleLine(){
	int i, j;
	for (i = 0; i < PLAY_ROW_N && !isFull(i); ++i);
	if (i == PLAY_ROW_N)
		return 0;
	for (--i; i >= 0; --i)
		for (j = 0; j < PLAY_COL_N; ++j){
			map[i + 1][j] = map[i][j];
			mapColor[i + 1][j] = mapColor[i][j];
		}
	memset(map[0], 0, sizeof(map[0]));
	memset(mapColor[0], 0, sizeof(mapColor[0]));
	return 1;
}

void clearLines(){
	int cntLines = 0;
	while (clearSingleLine())
		++cntLines;
	score += cntLines * cntLines;
	clearedLines += cntLines;
}

void getNextItem(){
	nextItem = getItem();
	nextItem.x = NEXT_ROW_N - 1;
	nextItem.y = 0;
}

void nextToFall(){
	do{
		fallItem = getLegalItem();
	}while (fallItem.id != nextItem.id);
	getNextItem();
}

Uint32 addItemToMap(ttsItem *t){
	int overUpSide = 0;
	int i, j, x, y;
	for (i = 0; i < SHAPE_SIZE; ++i)
		for (j = 0; j < SHAPE_SIZE; ++j)
			if (getShapeBit(t->id, i, j)){
				x = t->x - i;
				y = t->y + j;
				if (inRange(x, y)){
					map[x][y] = 1;
					mapColor[x][y] = t->color;
				}
				else
					overUpSide = 1;
			}
	return overUpSide;
}

void gameUpdate(){
	if (!moveDown(&fallItem)){
		if (addItemToMap(&fallItem)){
			gameStatus = GAME_End;
			return;
		}
		clearLines();
		nextToFall();
	}
}

void initGame(){
	gameStatus = GAME_Start;

	score = 0;
	clearedLines = 0;

	srand(time(NULL));

	fallItem = getLegalItem();
	getNextItem();

	memset(map, 0, sizeof(map));
	memset(mapColor, 0, sizeof(mapColor));
}
