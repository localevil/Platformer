#pragma once

#include <stdint.h>

typedef struct engine_options {
	const char *title;
	uint32_t width;
	uint32_t height;
}engine_options_t;

typedef struct engine engine_t;

engine_t *engine_init(engine_options_t *);
int engine_is_running(engine_t *);
int engine_handle_events(engine_t *);
int engine_update(engine_t *);
int engine_render(engine_t *);
int engine_delete(engine_t *);
