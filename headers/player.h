#pragma once

typedef struct player
{
	int (*getX)();
	int (*getY)();
	int (*getWidth)();
	int (*getHeight)();
	int (*getTextureId)();
	int (*getTextX)();
	int (*getTextY)();
	int x;
	int y;
	int width;
	int height;
	int textX;
	int textY;
	int textId;
}player_t;

player_t createPlayer();
