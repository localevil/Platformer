#pragma once
#include <stdint.h>
#include <SDL2/SDL.h>
#include "vector2d.h"

typedef struct tilemap tilemap_t;

tilemap_t *tilemap_create(SDL_Renderer* ren, const char * path, uint32_t size,
							uint32_t cols, uint32_t rows, uint32_t tile_width,
							uint32_t tile_height);
int tilemap_draw_tile(tilemap_t *, uint32_t, vector2d_t);
int tilemap_delete(tilemap_t *);
