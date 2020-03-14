#pragma once
#include <stdint.h>

typedef struct game_renderer game_renderer_t;
typedef struct graphic_object graphic_object_t;

typedef void (*fnUnderLoop)(const uint8_t*, graphic_object_t**);

int addTexture(const char*);
int addObject(graphic_object_t *);
int initRenderer(void);
int presentRenderer(fnUnderLoop underLoop);
int deleteRenderer(void);
