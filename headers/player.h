#pragma once
#include <time.h>

typedef struct player player_t;

player_t *createPlayer(int, int, int, int, int, int, int, int, int, int);
player_t * copyPlayer(player_t *);
void deletePlayer(player_t *);
