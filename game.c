#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "window.h"
#include "game.h"

Uint32 score;
Uint32 clearedLines;

Uint32 map[ROW_N];
ttsColor mapColor[ROW_N][COL_N];

ttsItem fall;

inline Uint32 getShapeDigit(ttsShape s, Uint32 i, Uint32 j){
	return !!(s & (1 << (i << 2 | j)));
}

inline ttsShape getConstTtsShape(Uint8 id){
	return constTtsShape[id >> 2][id & 3];
}

void initGame(){
	score = 0;
	clearedLines = 0;

	srand(time(NULL));

	fall = getLegalTtsItem();

	int i, j;
	for (i = 0; i < ROW_N; ++i){
		map[i] = (1 << COL_N) - 1;
		for (j = 0; j < COL_N; ++j)
			mapColor[i][j] = i << 19 | j << 4;
	}
}

int inRange(int x, int y){
	return 0 <= x && x < ROW_N && 0 <= y && y < COL_N;
}

inline Uint32 isOverUpSide(ttsItem *t){
	return t->x >= ROW_N;
}

inline Uint32 isOverDownSide(ttsItem *t){
	return t->x >= ROW_N;
}

inline Uint32 isOverLeftSide(ttsItem *t){
	return t->y >= COL_N;
}

inline Uint32 isOverRightSide(ttsItem *t){
	static ttsShape s;
	int i, j;
	s = getConstTtsShape(t->id);
	for (i = 0; i < 16; ++i)
		if (s & (1 << i) && t->y + (i & 3) >= COL_N)
			return 1;
	return 0;
}

Uint32 isLegal(ttsItem *t){
	return !isOverUpSide(t) && !isOverDownSide(t)
		&& !isOverLeftSide(t) && !isOverRightSide(t);
}

ttsItem getTtsItem(){
	ttsItem t;
	t.x = 0;
	t.y = rand() % COL_N + 8;
	t.id = rand() % 24;
	t.color = 0x007f7f7f;
	return t;
}

ttsItem getLegalTtsItem(){
	ttsItem t;
	do{
		t = getTtsItem();
	}while (isOverRightSide(&t));
	return t;
}
