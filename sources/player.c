#include "player.h"

int player_getX(player_t *p)
{
	return p->x;
}

int player_getY(player_t *p)
{
	return p->y;
}

int player_getWidth(player_t *p)
{
	return p->width;
}

int player_getHeight(player_t *p)
{
	return p->height;
}

int player_getTextureId(player_t *p)
{
	return p->textId;
}

int player_getTextX(player_t *p)
{
	return p->textX;
}

int player_getTextY(player_t *p)
{
	return p->textY;
}



void player_processAnimation(player_t *p)
{
    static int count = 0;
    p->textX = count * p->height;
    if (count < 3)
        count++;
    else
        count = 0;
//    p->x = p->x + p->vel;
}

int player_getVel(struct player * p)
{
    return p->vel;
}

void player_setX(struct player* p, int newX)
{
    p->x = newX;
}

void player_setY(struct player* p, int newY)
{
    p->y = newY;
}

player_t createPlayer()
{
	player_t p = {
		player_getX,
		player_getY,
		player_getWidth,
		player_getHeight,
		player_getTextureId,
		player_getTextX,
        player_getTextY,
        player_processAnimation,
        player_getVel,
        player_setX,
        player_setY,
        0,0,0,0,0,0,0,0,{0}
	};
	return p;
}

