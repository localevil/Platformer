#include "game_object.h"

#include <stdlib.h>
#include <vector2d.h>

struct game_object {
	vector2d_t pos;
	uint32_t width;
	uint32_t height;
	uint32_t tile_id;
	uint8_t first_frame;
	uint8_t flip;
	tilemap_t *tm;
};

vector2d_t game_object_get_pos(game_object_t *p)
{
	return p->pos;
}

vector2d_t game_object_set_pos(game_object_t *p, vector2d_t pos)
{
	p->pos = pos;
	return p->pos;
}
uint32_t game_object_get_width(game_object_t *p)
{
	return p->width;
}

uint32_t game_object_get_height(game_object_t *p)
{
	return p->height;
}

uint32_t game_object_process_animation(game_object_t *p)
{
	static const uint8_t ANIMATION_COUNT = 3;
	if (p->tile_id < p->first_frame + ANIMATION_COUNT)
		p->tile_id++;
	else
		p->tile_id = p->first_frame;
	return 0;
}

uint32_t game_object_update(game_object_t *p)
{
	game_object_process_animation(p);
	return 0;
}

uint32_t game_object_set_flip(game_object_t *p, uint8_t flip)
{
	p->flip = flip;
	return 0;
}

uint8_t game_object_get_flip(game_object_t *p)
{
	return p->flip;
}


uint32_t game_object_draw(game_object_t *p)
{
	tilemap_draw_tile(p->tm, p->tile_id, p->pos, p->flip);
	return 0;
}

uint32_t game_object_move(game_object_t *p, vector2d_t d)
{
	p->pos = vector2d_add(p->pos, d);
	return 0;
}

game_object_t *game_object_create(uint32_t width, uint32_t heigth, vector2d_t pos,
						uint32_t tile_id, tilemap_t *tm)
{

	game_object_t *p = (game_object_t*)malloc(sizeof(game_object_t));
		p->pos = pos;
		p->width = width;
		p->height = heigth;
		p->tile_id = tile_id;
		p->flip = 0;
		p->first_frame = tile_id;
		p->tm = tm;
	return p;
}

//game_object_t *copyPlayer(game_object_t *p1)
//{
//	game_object_t *p2 = NULL;
//	if (p1 != NULL)
//	{
//		p2 = (game_object_t *)malloc(sizeof (game_object_t));
//		*p2 = *p1;
//	}
//	return p2;
//}

void game_object_delete(game_object_t *p)
{
	if (p != NULL)
	{
		free(p);
	}
}

