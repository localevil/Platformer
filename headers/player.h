#pragma once
#include <time.h>

typedef enum duratuin {
	LEFT,
	RIGHT,
	UP,
	DOWN
}duration_t;

typedef struct player player_t;

player_t *player_create(int, int, int, int, int, int, int, int);
player_t * player_copy(player_t *);

int player_get_x(player_t *p);
int player_get_y(player_t *p);
int player_get_text_x(player_t *p);
int player_get_text_y(player_t *p);
int player_get_text_width(player_t *p);
int player_get_text_height(player_t *p);

int player_set_on_floor(player_t *p, int flag);

int player_on_floor(player_t *p);
int player_process_animation(player_t *p);
int player_move(player_t*, duration_t);

void player_delete(player_t *);
