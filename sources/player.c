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
        0,0,0,0,0,0,0
	};
	return p;
}

