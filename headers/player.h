#pragma once
#include <time.h>

//#define STRUCT_FUNC(return_type, name) return_type (*name)(struct player*)

typedef struct player
{
    int (*getX)(struct player*);
    int (*getY)(struct player*);
    int (*getWidth)(struct player*);
    int (*getHeight)(struct player*);
    int (*getTextureId)(struct player*);
    int (*getTextX)(struct player*);
    int (*getTextY)(struct player*);
    void (*processAnumation)(struct player*);
    int (*getVel)(struct player*);
    void (*setX)(struct player*, int);
    void (*setY)(struct player*, int);
	int x;
	int y;
	int width;
	int height;
	int textX;
	int textY;
	int textId;
    int vel;
    struct timespec currentTimeStamp;
}player_t;

player_t createPlayer(void);
