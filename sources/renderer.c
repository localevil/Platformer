#include "renderer.h"

#include <SDL2/SDL.h>

#include <stdio.h>

#define CREATE_DUMMY(count) int (*dummy ## count)(graphic_object_t *)
typedef int (*fnPtr)(graphic_object_t*);

typedef struct graphic_object
{
	fnPtr getX;
	fnPtr getY;
	CREATE_DUMMY(0);
	CREATE_DUMMY(1);
	fnPtr getTextureId;
	fnPtr getTextX;
	fnPtr getTextY;
	fnPtr getTextWidth;
	fnPtr getTextHeight;
	fnPtr processAnimation;
}graphic_object_t;

static SDL_Window *window;
static SDL_Renderer *renderer;

static SDL_Texture *textures[10] = {0};
static int lastTextInList = 0;

static graphic_object_t *objects[10] = {0};
static int lastObjInList = 0;

static const Uint8 *keys = 0;

#define ANIMATION_DELAY 250
#define RENDER_DELAY 16



int addObject(graphic_object_t *obj)
{
	if (lastObjInList >= 10)
		return 1;

	objects[lastObjInList++] = obj;
	return 0;
}

int presentRenderer(fnUnderLoop underLoop)
{
	int quit = 0;
	unsigned int animationLastTime = 0, renderLastTime = 0;
	int framsCount = 0;
	while(!quit)
	{
		static SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch (event.type) {
			case SDL_QUIT:
				quit = 1;
				break;
			}
		}

		underLoop(keys, objects);

		unsigned int currentTime = SDL_GetTicks();
		if (currentTime > animationLastTime + ANIMATION_DELAY)
		{
			for (int i = 0; i < lastObjInList; i++)
			{
				struct graphic_object *obj = objects[i];
				obj->processAnimation(obj);
			}
			animationLastTime = currentTime;
		}

		if (currentTime > renderLastTime + RENDER_DELAY)
		{
			if (renderer == NULL)
				return 1;

			SDL_RenderClear(renderer);
			//renderObjects();
			SDL_RenderPresent(renderer);
			renderLastTime = currentTime;
			framsCount++;
		}

	}
	return 0;
}

int deleteRenderer()
{
	for (int i = 0; i < lastTextInList; i++)
	{
		SDL_DestroyTexture(textures[i]);
	}

	if (window == NULL || renderer == NULL)
		return 1;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;
}
