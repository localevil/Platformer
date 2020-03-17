#include "player.h"
#include <stdlib.h>
#include <stdint.h>

struct player {
	int x;
	int y;
	int width;
	int height;
	int textX;
	int textY;
	int textWidth;
	int textHeight;
	int on_floor;
};

int player_get_x(player_t *p)
{
	return p->x;
}

int player_get_y(player_t *p)
{
	return p->y;
}

int player_get_width(player_t *p)
{
	return p->width;
}

int player_get_height(player_t *p)
{
	return p->height;
}

int player_get_text_x(player_t *p)
{
	return p->textX;
}

int player_get_text_y(player_t *p)
{
	return p->textY;
}

int player_get_text_width(player_t *p)
{
	return p->textWidth;
}

int player_get_text_height(player_t *p)
{
	return p->textHeight;
}

int player_set_on_floor(player_t *p, int flag)
{
	return p->on_floor = flag;
}

int player_on_floor(player_t *p)
{
	return p->on_floor;
}

int player_process_animation(player_t *p)
{
	static int count = 0;
	p->textX = count * p->textHeight;
	if (count < 3)
		count++;
	else
		count = 0;
	return 0;
}

int player_move(player_t *p, duration_t d)
{
	static const uint8_t JUMP = 250;
	static const uint8_t VEL = 1;

	switch (d) {
	case LEFT:
		p->x -= VEL;
		break;
	case RIGHT:
		p->x += VEL;
		break;
	case UP:
		if (p->y > p->y + JUMP)
		{
			return 1;
		}
		p->y -= VEL;
		break;
	case DOWN:
		p->y += VEL;
		break;
	}
	return 0;
}

player_t *player_create(int width, int heigth, int textX, int textY, int textWidth, int textHeight, int x, int y)
{

	player_t *p = (player_t*)malloc(sizeof(player_t));
		p->x = x;
		p->y = y;
		p->width = width;
		p->height = heigth;
		p->textX = textX;
		p->textY = textY;
		p->textWidth = textWidth;
		p->textHeight = textHeight;
		p->on_floor = 0;
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

