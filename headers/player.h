#pragma once
#include <stdint.h>
#include "game_object.h"

typedef game_object_t player_t;

int player_handle_events(game_object_t *p, const uint8_t *keys);
