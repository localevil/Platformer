#pragma once

typedef struct player
{
    int (*getX)(struct player*);
    int (*getY)(struct player*);
    int (*getWidth)(struct player*);
    int (*getHeight)(struct player*);
    int (*getTextureId)(struct player*);
    int (*getTextX)(struct player*);
    int (*getTextY)(struct player*);
	int x;
	int y;
	int width;
	int height;
	int textX;
	int textY;
	int textId;
    int vel;
}player_t;

player_t createPlayer(void);
