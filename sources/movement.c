#include "movement.h"
#include <SDL2/SDL.h>

#define CREATE_DUMMY(count) int (*dummy ## count)(movement_object_t *)

typedef int (*fnPtr)(movement_object_t *);
typedef int (*fnPtrInt)(movement_object_t *, int);

typedef struct movement_object{
    fnPtr getX;
    fnPtr getY;
    CREATE_DUMMY(1);
    CREATE_DUMMY(2);
    CREATE_DUMMY(3);
    CREATE_DUMMY(4);
    CREATE_DUMMY(5);
    CREATE_DUMMY(6);
    CREATE_DUMMY(7);
    CREATE_DUMMY(8);
    fnPtr getVel;
    fnPtrInt setX;
    fnPtrInt setY;
}movement_object_t;

static const int EVENT_DELAY = 25;

void player_movement(movement_object_t *p, const uint8_t* keys)
{
    static unsigned int lastTime = 0;
    unsigned int currentTime = SDL_GetTicks();
    if (currentTime > lastTime + EVENT_DELAY)
    {
        if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
            p->setX(p, p->getX(p) - p->getVel(p));
        if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
            p->setX(p, p->getX(p) + p->getVel(p));
        if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])
            p->setY(p, p->getY(p) - p->getVel(p));
        else
            p->setY(p, p->getY(p) + p->getVel(p));
        lastTime = currentTime;

    }
}
