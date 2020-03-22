#include "player.h"
#include <SDL2/SDL.h>

typedef game_object_t shot_t;

struct player {
	game_object_t *go;
	shot_t *shot;
	uint8_t shoting;
};

player_t *player_create(game_object_t *go, tilemap_t *shot_tm)
{
	player_t *p = (player_t *)malloc(sizeof (player_t));
	p->go = go;

	const uint8_t COLLISION_WIDTH = 16;
	const uint8_t COLLISION_HEIGHT = 22;

	vector2d_t shot_pos = {0,0};
	p->shot = game_object_create(COLLISION_WIDTH, COLLISION_HEIGHT, shot_pos, 0,
									shot_tm);
	p->shoting = 0;
	return p;
}

uint32_t player_update_shot(player_t * p)
{
	const uint8_t flip = game_object_get_flip(p->go);
	vector2d_t shift = {10,-15};
	vector2d_t pos = game_object_get_pos(p->go);
	if (flip)
	{
		vector2d_t muliplier = {-1, 1};
		shift = vector2d_multiply(shift, muliplier);
	}
	game_object_set_flip(p->shot, flip);
	game_object_set_pos(p->shot, vector2d_add(pos, shift));
	return 0;
}

uint32_t player_handle_events(player_t *p, const uint8_t *keys)
{
	static const uint8_t EVENT_DELAY = 5;

	static uint32_t lastTime = 0;
	uint32_t currentTime = SDL_GetTicks();
	if (currentTime > lastTime + EVENT_DELAY)
	{
		uint8_t game_object_flip = game_object_get_flip(p->go);
		vector2d_t duration = {0};
		if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
		{
			duration.x--;
			game_object_flip = SDL_FLIP_HORIZONTAL;
		}
		if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
		{
			duration.x++;
			game_object_flip = SDL_FLIP_NONE;
		}
		if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])
		{
			duration.y--;
		}
		if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S])
		{
			duration.y++;
		}
		if(keys[SDL_SCANCODE_SPACE])
		{

			p->shoting = 3;
		}

		game_object_move(p->go, vector2d_normalize(duration));
		game_object_set_flip(p->go, game_object_flip);
		player_update_shot(p);
		lastTime = currentTime;
	}
	return 0;
}

uint32_t player_draw(player_t *p)
{
	game_object_draw(p->go);
	if (p->shoting)
	{
		game_object_draw(p->shot);
	}
	return 0;
}

uint32_t player_update(player_t *p)
{
	game_object_update(p->go);
	if (p->shoting)
	{
		game_object_update(p->shot);
		p->shoting--;
	}
	return 0;
}

uint32_t player_delete(player_t *p)
{
	if (p != NULL)
	{
		if (p->go != NULL)
			game_object_delete(p->go);
		free(p);
	}
	return 0;
}
