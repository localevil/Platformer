#pragma once
#include <stdint.h>
#include "game_object.h"
#include "vector2d.h"

typedef struct enemy enemy_t;

enemy_t *enemy_create(game_object_t *gm, vector2d_t d);
uint32_t enemy_update(enemy_t *);
uint32_t enemy_draw(enemy_t *);
uint32_t enemy_delete(enemy_t *e);
