#include "player.h"
#include <stdlib.h>

typedef int (*fnPtr) (player_t*);

typedef int (*fnPtrInt)(player_t*, int);

typedef struct player {
   fnPtr getX;
   fnPtr getY;
   fnPtr getWidth;
   fnPtr getHeight;
   fnPtr getTextureId;
   fnPtr getTextX;
   fnPtr getTextY;
   fnPtr getTextWidth;
   fnPtr getTextHeight;
   fnPtr processAnumation;
   fnPtr getVel;
   fnPtrInt setX;
   fnPtrInt setY;
   int x;
   int y;
   int width;
   int height;
   int textX;
   int textY;
   int textWidth;
   int textHeight;
   int textId;
   int vel;
}player_t;

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

int player_getTextWidth(player_t *p)
{
    return p->textWidth;
}

int player_getTextHeight(player_t *p)
{
    return p->textHeight;
}

int player_processAnimation(player_t *p)
{
    static int count = 0;
    p->textX = count * p->textHeight;
    if (count < 3)
        count++;
    else
        count = 0;
    return 0;
}

int player_getVel(player_t * p)
{
    return p->vel;
}

int player_setX(player_t* p, int newX)
{
    p->x = newX;
    return 0;
}

int player_setY(player_t* p, int newY)
{
    p->y = newY;
    return 0;
}

player_t *createPlayer(int textId, int width, int heigth, int textX, int textY, int textWidth, int textHeight, int x, int y, int vel)
{

    player_t *p = (player_t*)malloc(sizeof(player_t));
        p->getX = player_getX;
        p->getY = player_getY;
        p->getWidth = player_getWidth;
        p->getHeight = player_getHeight;
        p->getTextureId = player_getTextureId;
        p->getTextX = player_getTextX;
        p->getTextY = player_getTextY;
        p->getTextWidth = player_getTextWidth;
        p->getTextHeight = player_getTextHeight;
        p->processAnumation = player_processAnimation;
        p->getVel = player_getVel;
        p->setX = player_setX;
        p->setY = player_setY;
        p->x = x;
        p->y = y;
        p->vel = vel;
        p->width = width;
        p->height = heigth;
        p->textId = textId;
        p->textX = textX;
        p->textY = textY;
        p->textWidth = textWidth;
        p->textHeight = textHeight;
	return p;
}

player_t *copyPlayer(player_t *p1)
{
    player_t *p2 = NULL;
    if (p1 != NULL)
    {
        p2 = (player_t *)malloc(sizeof (player_t));
        *p2 = *p1;
    }
    return p2;
}

void deletePlayer(player_t *p)
{
    if (p != NULL)
        free(p);
}

