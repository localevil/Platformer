#include "engine.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "player.h"

static const uint8_t COLLISION_WIDTH = 16;
static const uint8_t COLLISION_HEIGHT = 22;
static const uint8_t TEXTURE_CELL = 32;

struct engine {
	uint8_t running;
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Texture *textures[10];
	int lastTextInList;

	player_t *player;
	const uint8_t *keys;
};

static int add_texture(engine_t *e, const char* path)
{
	int result = 0;
	SDL_Surface * loadSurf = IMG_Load(path);

	SDL_Texture *newTexture = SDL_CreateTextureFromSurface(e->renderer, loadSurf);
	if (newTexture != NULL)
	{
		e->textures[e->lastTextInList] = newTexture;
		result = e->lastTextInList++;
	}else
	{
		printf("%s\n", SDL_GetError());
		return -1;
	}
	SDL_FreeSurface(loadSurf);
	return result;

}

static int render_player(engine_t *e)
{
	SDL_Rect dst = {player_get_x(e->player),
					player_get_y(e->player),
					player_get_text_width(e->player),
					player_get_text_height(e->player)};
	SDL_Rect src = {player_get_text_x(e->player),
					player_get_text_y(e->player),
					player_get_text_width(e->player),
					player_get_text_height(e->player)};

	if (SDL_RenderCopy(e->renderer, e->textures[0], &src, &dst) < 0)
	{
		printf("%s\n", SDL_GetError());
	}
	return 0;
}

engine_t *engine_init(engine_options_t *e_options)
{
	engine_t *e = (engine_t *)malloc(sizeof (engine_t));

	e->running = 0;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("SDL init failed: %s\n", SDL_GetError());
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
	}

	e->renderer = SDL_CreateRenderer(e->window,0,0);
	if (e->renderer == NULL) {
		printf("Create renderer failed: %s\n", SDL_GetError());
	} else {
		e->running = 1;
	}
	add_texture(e, "assets/characters.png");
	e->player = player_create(	COLLISION_WIDTH,
								COLLISION_HEIGHT,
								0,
								2 * TEXTURE_CELL,
								TEXTURE_CELL,
								TEXTURE_CELL,
								0,
								0);

	e->keys = SDL_GetKeyboardState(NULL);
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

	static const uint8_t EVENT_DELAY = 25;

	static uint32_t lastTime = 0;
	uint32_t currentTime = SDL_GetTicks();
	if (currentTime > lastTime + EVENT_DELAY)
	{
		if (e->keys[SDL_SCANCODE_LEFT] || e->keys[SDL_SCANCODE_A])
			player_move(e->player, LEFT);
		if (e->keys[SDL_SCANCODE_RIGHT] || e->keys[SDL_SCANCODE_D])
			player_move(e->player, RIGHT);
		if (e->keys[SDL_SCANCODE_UP] || e->keys[SDL_SCANCODE_W])
			player_move(e->player, UP);
		else if (e->keys[SDL_SCANCODE_DOWN] || e->keys[SDL_SCANCODE_S])
			player_move(e->player, DOWN);
		lastTime = currentTime;
	}

	return 0;
}

int engine_update(engine_t *e)
{
	static const uint8_t ANIMATION_DELAY = 250;
	static uint32_t lastTime = 0;

	uint32_t currentTime = SDL_GetTicks();
	if (currentTime > lastTime + ANIMATION_DELAY)
	{
		player_process_animation(e->player);
		lastTime = currentTime;
	}
	return 0;
}

int engine_render(engine_t *e)
{
	SDL_RenderClear(e->renderer);
	render_player(e);
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
