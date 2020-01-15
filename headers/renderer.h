#pragma once
#include <stdint.h>

struct grafic_object;

int addTexture(const char* path);
int addObject(struct grafic_object *obj);
int initRenderer(void);
int presentRenderer(void (*underLoop)(const uint8_t *));
int deleteRenderer(void);
