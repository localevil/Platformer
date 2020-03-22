#pragma once
#include <stdint.h>
#include "tilemap.h"
#include "vector2d.h"

typedef struct player player_t;

player_t *player_create(uint32_t, uint32_t, vector2d_t, uint32_t,
						tilemap_t *);
//player_t * player_copy(player_t *);

uint32_t player_set_on_floor(player_t *p, uint8_t flag);

uint32_t player_on_floor(player_t *p);
uint32_t player_renderer(player_t *);
uint32_t player_update(player_t *p);
uint32_t player_move(player_t*, vector2d_t);

void player_delete(player_t *);
