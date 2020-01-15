#include "movement.h"
#include <SDL2/SDL.h>

#define CREATE_DUMMY(count) int (*dummy ## count)(struct movement_object *)

struct movement_object{
    int (*getX)(struct movement_object *);
    int (*getY)(struct movement_object *);
    CREATE_DUMMY(1);
    CREATE_DUMMY(2);
    CREATE_DUMMY(3);
    CREATE_DUMMY(4);
    CREATE_DUMMY(5);
    CREATE_DUMMY(6);
    int (*getVel)(struct movement_object*);
    void (*setX)(struct movement_object *, int);
    void (*setY)(struct movement_object *, int);
};

#define EVENT_DELAY 25

void player_movement(movement_object_t *p, const uint8_t* keys)
{
    static unsigned int lastTime = 0;
    unsigned int currentTime = SDL_GetTicks();
    if (currentTime > lastTime + EVENT_DELAY)
    {
        if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])
            p->setY(p, p->getY(p) - p->getVel(p));
        if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S])
            p->setY(p, p->getY(p) + p->getVel(p));
        if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
            p->setX(p, p->getX(p) - p->getVel(p));
        if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
            p->setX(p, p->getX(p) + p->getVel(p));
        lastTime = currentTime;
    }
}
