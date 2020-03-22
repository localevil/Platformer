#include "player.h"

int player_handle_events(player_t *p, const uint8_t *keys)
{
	static const uint8_t EVENT_DELAY = 5;

	static uint32_t lastTime = 0;
	uint32_t currentTime = SDL_GetTicks();
	if (currentTime > lastTime + EVENT_DELAY)
	{
		static SDL_RendererFlip game_object_flip = SDL_FLIP_NONE;
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
		if (keys[SDL_SCANCODE_UP])
		{
			duration.y--;
		}
		if (keys[SDL_SCANCODE_DOWN])
		{
			duration.y++;

		}
		game_object_move(p, vector2d_normalize(duration));
		game_object_set_flip(p, game_object_flip);

		lastTime = currentTime;
	}

	return 0;
}
