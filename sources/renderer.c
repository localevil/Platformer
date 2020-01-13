#include "renderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

struct grafic_object
{
    int (*getX)(struct grafic_object*);
    int (*getY)(struct grafic_object*);
    int (*getWidth)(struct grafic_object*);
    int (*getHeight)(struct grafic_object*);
    int (*getTextureId)(struct grafic_object*);
    int (*getTextX)(struct grafic_object*);
    int (*getTextY)(struct grafic_object*);
};

static SDL_Window *window;
static SDL_Renderer *renderer;

static SDL_Texture *textures[10] = {0};
static int lastTextInList = 0;

static struct grafic_object *objects[10] = {0};
static int lastObjInList = 0;

int addTexture(const char* path)
{
	if (lastTextInList >= 10)
        return -1;

    int result = 0;
    SDL_Surface * loadSurf = IMG_Load(path);

    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, loadSurf);
    if (newTexture != NULL)
    {
        textures[lastTextInList] = newTexture;
        result = lastTextInList++;
    }else
    {
        printf("%s\n", SDL_GetError());
    }
    SDL_FreeSurface(loadSurf);
    return result;
	
}

int addObject(struct grafic_object *obj)
{
	if (lastObjInList >= 10)
		return 1;

	objects[lastObjInList++] = obj;
	return 0;
}

static int renderObjects()
{
    for (int i = 0; i < lastObjInList; ++i)
	{
		struct grafic_object *currentObj = objects[i];
		SDL_Rect dst = {currentObj->getX(currentObj), currentObj->getY(currentObj), currentObj->getWidth(currentObj), currentObj->getHeight(currentObj)};
        SDL_Rect src = {currentObj->getTextX(currentObj), currentObj->getTextY(currentObj), currentObj->getWidth(currentObj), currentObj->getHeight(currentObj)};
        if (SDL_RenderCopy(renderer, textures[currentObj->getTextureId(currentObj)], &src, &dst) < 0)
        {
            printf("%s\n", SDL_GetError());
        }
	}
	return 0;
}

int initRenderer()
{
	SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("King story", 0, 0, 640, 480, 0);
	if (window == NULL)
		return 1;
	renderer = SDL_CreateRenderer(window, 0, 0);
	if (renderer == NULL)
        return 1;
    IMG_Init(IMG_INIT_PNG);
	return 0;
}

int presentRenderer(void (*underLoop)(void))
{
	bool quit = false;
    unsigned int lastTime = 0;
	while(!quit)
	{
		static SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			}
        }

        unsigned int currentTime = SDL_GetTicks();
        if (currentTime > lastTime + 600)
        {
            if (underLoop != NULL)
                underLoop();

            if (renderer == NULL)
                return 1;

            SDL_RenderClear(renderer);
            renderObjects();
            SDL_RenderPresent(renderer);
            lastTime = currentTime;
            continue;
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
