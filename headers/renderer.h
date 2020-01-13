#pragma once

struct grafic_object;

int addTexture(const char* path);
int addObject(struct grafic_object *obj);
int initRenderer(void);
int presentRenderer(void (*)());
int deleteRenderer(void);
