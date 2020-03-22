#pragma once
#include <stdint.h>
#include "game_object.h"
#include "tilemap.h"

typedef struct player player_t;

player_t *player_create(game_object_t *go, tilemap_t *shot);
uint32_t player_handle_events(player_t *p, const uint8_t *keys);
uint32_t player_draw(player_t *p);
uint32_t player_update(player_t *p);
uint32_t player_delete(player_t *p);
