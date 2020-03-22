#include "enemy.h"
#include <stdlib.h>

struct enemy {
	game_object_t *go;
	vector2d_t duration;
};

enemy_t *enemy_create(game_object_t *go, vector2d_t d)
{
	enemy_t *e = (enemy_t*)malloc(sizeof (enemy_t));
	e->go = go;
	e->duration = d;
	return e;
}

uint32_t enemy_update(enemy_t *e)
{
	vector2d_t pos = game_object_get_pos(e->go);
	vector2d_t new_duration = e->duration;
	if (pos.x >=640 || pos.x <= 0)
	{
		new_duration.x = -new_duration.x;
		e->duration= new_duration;
		new_duration.y = 10;

		if (pos.x <= 0)
			game_object_set_flip(e->go, SDL_FLIP_NONE);
		else
			game_object_set_flip(e->go, SDL_FLIP_HORIZONTAL);
	}

	game_object_move(e->go, new_duration);
	return 0;
}

uint32_t enemy_draw(enemy_t *e)
{
	game_object_draw(e->go);
	return 0;
}

uint32_t enemy_delete(enemy_t *e)
{
	if (e != NULL)
	{
		if (e->go != NULL)
			game_object_delete(e->go);
		free(e);
	}
	return 0;
}
