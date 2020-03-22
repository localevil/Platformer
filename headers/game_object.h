#pragma once
#include <stdint.h>
#include "tilemap.h"
#include "vector2d.h"

typedef struct game_object game_object_t;

game_object_t *game_object_create(uint32_t, uint32_t, vector2d_t, uint32_t,
						tilemap_t *);
//game_object_t * game_object_copy(game_object_t *);

vector2d_t game_object_get_pos(game_object_t *);
uint32_t game_object_draw(game_object_t *);
uint32_t game_object_update(game_object_t *p);
uint32_t game_object_move(game_object_t*, vector2d_t);
uint32_t game_object_set_flip(game_object_t *p, uint8_t flip);

void game_object_delete(game_object_t *);
