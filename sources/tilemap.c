#include "tilemap.h"
#include <SDL2/SDL_image.h>

struct tilemap {
	SDL_Renderer * renderer;
	SDL_Texture *texture;
	uint32_t size;
	uint32_t colums;
	uint32_t rows;
	uint32_t tile_width;
	uint32_t tile_height;
};

tilemap_t *tilemap_create(SDL_Renderer* ren, const char * path, uint32_t size,
							uint32_t cols, uint32_t rows, uint32_t tile_width,
							uint32_t tile_height)
{
	tilemap_t *tm = NULL;

	SDL_Surface * load_surface = IMG_Load(path);
	if (load_surface != NULL)
	{
		SDL_Texture *new_texture = SDL_CreateTextureFromSurface(ren,
																load_surface);
		if (new_texture != NULL)
		{
			tm = (tilemap_t *)malloc(sizeof (tilemap_t));
			tm->renderer = ren;
			tm->texture = new_texture;
			tm->size = size;
			tm->colums = cols;
			tm->rows = rows;
			tm->tile_width = tile_width;
			tm->tile_height = tile_height;
		}
		else
		{
			printf("Texture %s not creating: %s\n", path, SDL_GetError());
		}
		SDL_FreeSurface(load_surface);
	}
	else
	{
		printf("Loading %s failed: %s\n", path, SDL_GetError());
	}

	return tm;
}

int tilemap_draw_tile(tilemap_t * tm, uint32_t tile_id, vector2d_t pos,
						uint8_t flip)
{
	if (tile_id > tm->size)
			return -1;
	uint32_t col = tile_id % tm->colums;
	uint32_t row = tile_id / tm->rows;
	SDL_Rect dst = {pos.x, pos.y, tm->tile_width, tm->tile_height};
	SDL_Rect src = {col * tm->tile_width, row * tm->tile_width, tm->tile_width, tm->tile_height};

	if (SDL_RenderCopyEx(tm->renderer, tm->texture, &src, &dst, 0, NULL, flip) < 0)
	{
		printf("%s\n", SDL_GetError());
		return -1;
	}
	return 0;
}

int tilemap_delete(tilemap_t *tm)
{
	if (tm != NULL)
	{
		if (tm->texture != NULL)
			SDL_DestroyTexture(tm->texture);
		free(tm);
	}
	return 0;
}
