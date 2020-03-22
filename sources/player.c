#include "player.h"

#include <stdlib.h>
#include <vector2d.h>

struct player {
	vector2d_t pos;
	uint32_t width;
	uint32_t height;
	uint32_t tile_id;
	uint8_t on_floor;
	tilemap_t *tm;
};

vector2d_t player_get_pos(player_t *p)
{
	return p->pos;
}

uint32_t player_get_width(player_t *p)
{
	return p->width;
}

uint32_t player_get_height(player_t *p)
{
	return p->height;
}


uint32_t player_set_on_floor(player_t *p, uint8_t flag)
{
	return p->on_floor = flag;
}

uint32_t player_on_floor(player_t *p)
{
	return p->on_floor;
}

uint32_t player_process_animation(player_t *p)
{
	static const uint8_t ANIMATION_DELAY = 250;
	static uint32_t lastTime = 0;

	uint32_t currentTime = SDL_GetTicks();
	if (currentTime > lastTime + ANIMATION_DELAY)
	{
		static const uint8_t ANIMATION_COUNT = 3;
		static uint8_t counter = 0;
		if (counter < ANIMATION_COUNT)
		{
			p->tile_id++;
			counter++;
		}
		else
		{
			p->tile_id -= ANIMATION_COUNT;
			counter = 0;
		}
		lastTime = currentTime;
	}
	return 0;
}

uint32_t player_update(player_t *p)
{
	player_process_animation(p);
	return 0;
}

uint32_t player_renderer(player_t *p)
{
	tilemap_draw_tile(p->tm, p->tile_id, p->pos);
	return 0;
}

uint32_t player_move(player_t *p, vector2d_t d)
{
	p->pos = vector2d_add(p->pos, d);
	return 0;
}

player_t *player_create(uint32_t width, uint32_t heigth, vector2d_t pos,
						uint32_t tile_id, tilemap_t * tm)
{

	player_t *p = (player_t*)malloc(sizeof(player_t));
		p->pos = pos;
		p->width = width;
		p->height = heigth;
		p->tile_id = tile_id;
		p->tm = tm;
		p->on_floor = 0;
	return p;
}

//player_t *copyPlayer(player_t *p1)
//{
//	player_t *p2 = NULL;
//	if (p1 != NULL)
//	{
//		p2 = (player_t *)malloc(sizeof (player_t));
//		*p2 = *p1;
//	}
//	return p2;
//}

void player_delete(player_t *p)
{
	if (p != NULL)
		free(p);
}

