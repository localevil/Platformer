#include "engine.h"

#include <stdlib.h>
#include <SDL2/SDL.h>

#include "player.h"
#include "tilemap.h"
#include "vector2d.h"

struct engine {
	uint8_t running;
	SDL_Window *window;
	SDL_Renderer *renderer;

	tilemap_t * creatures;

	player_t *player;
	const uint8_t *keys;
};

engine_t *engine_init(engine_options_t *e_options)
{
	engine_t *e = (engine_t *)malloc(sizeof (engine_t));

	e->running = 1;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL init failed: %s\n", SDL_GetError());
		e->running = 0;
	}

	if (e_options == NULL) {
		e_options->title = "Default title";
		e_options->width = 640;
		e_options->height = 420;
	}
	e->window = SDL_CreateWindow(e_options->title,
										 SDL_WINDOWPOS_CENTERED,
										 SDL_WINDOWPOS_CENTERED,
										 e_options->width,
										 e_options->height,
										 0);
	if (e->window == NULL) {
		printf("Create window failed: %s\n", SDL_GetError());
		e->running = 0;
	}

	e->renderer = SDL_CreateRenderer(e->window,0,0);
	if (e->renderer == NULL) {
		printf("Create renderer failed: %s\n", SDL_GetError());
		e->running = 0;
	}
		static const uint8_t TILE_CELL = 32;
	e->creatures = tilemap_create(e->renderer, "assets/characters.png",
									73, 4, 23, TILE_CELL, TILE_CELL);
	if (e->creatures == NULL)
	{
		e->running = 0;
	}

	static const uint8_t COLLISION_WIDTH = 16;
	static const uint8_t COLLISION_HEIGHT = 22;

	vector2d_t player_pos = {0, 420 - TILE_CELL};
	e->player = player_create(COLLISION_WIDTH, COLLISION_HEIGHT, player_pos,
								23, e->creatures);

	e->keys = SDL_GetKeyboardState(NULL);

	e->running = 1;
	return e;
}

int engine_is_running(engine_t *e)
{
	return e->running;
}

int engine_handle_events(engine_t *e)
{
	static SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_QUIT:
			e->running = 0;
			break;
		}
	}

	static const uint8_t EVENT_DELAY = 5;

	static uint32_t lastTime = 0;
	uint32_t currentTime = SDL_GetTicks();
	if (currentTime > lastTime + EVENT_DELAY)
	{
		vector2d_t duration = {0};
		if (e->keys[SDL_SCANCODE_LEFT] || e->keys[SDL_SCANCODE_A])
			duration.x--;
		if (e->keys[SDL_SCANCODE_RIGHT] || e->keys[SDL_SCANCODE_D])
			duration.x++;
		if (e->keys[SDL_SCANCODE_UP])
			duration.y--;
		if (e->keys[SDL_SCANCODE_DOWN])
			duration.y++;
		player_move(e->player, vector2d_normalize(duration));
		lastTime = currentTime;
	}

	return 0;
}

int engine_update(engine_t *e)
{
	player_update(e->player);
	return 0;
}

int engine_render(engine_t *e)
{
	SDL_RenderClear(e->renderer);
	player_renderer(e->player);
	SDL_RenderPresent(e->renderer);
	return 0;
}

int engine_delete(engine_t *e)
{
	if (e->renderer !=NULL)
		SDL_DestroyRenderer(e->renderer);
	if (e->window !=NULL)
		SDL_DestroyWindow(e->window);
	free(e);
	return 0;
}
