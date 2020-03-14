#include <stdio.h>

#include "renderer.h"
#include "player.h"
#include "movement.h"
#include "collision.h"

static const int COLLISION_WIDTH = 16;
static const int COLLISION_HEIGHT = 22;
static const int TEXTURE_CELL = 32;
static const int SPEED = 1;
void underLoop(const uint8_t *keys, graphic_object_t **objects)
{
    player_t *prePl = copyPlayer((player_t *)objects[0]);

    player_movement((movement_object_t*)prePl, keys);
    for (int i = 1; i < 10; ++i)
    {
        if (prePl == NULL || objects[i] == NULL)
            break;
        if (check_collision((collision_object_t*) prePl, (collision_object_t *)objects[i]))
        {
            return;
        }
    }
    deletePlayer((player_t*) objects[0]);
    objects[0] = (graphic_object_t *)prePl;
}

int main()
{
    initRenderer();
    int charTextId = addTexture("characters.png");
    player_t *pl = createPlayer(charTextId,COLLISION_WIDTH,COLLISION_HEIGHT,0, 2 * TEXTURE_CELL,TEXTURE_CELL,TEXTURE_CELL, 0, 0, SPEED);

    player_t *creep1 = createPlayer(charTextId,COLLISION_WIDTH,COLLISION_HEIGHT,0, 1 * TEXTURE_CELL,TEXTURE_CELL,TEXTURE_CELL, 100, 100, 0);
    player_t *creep2 = createPlayer(charTextId,COLLISION_WIDTH,COLLISION_HEIGHT,0, 1 * TEXTURE_CELL,TEXTURE_CELL,TEXTURE_CELL, 200, 100, 0);

    addObject((struct graphic_object*)pl);
    addObject((struct graphic_object*)creep1);
    addObject((struct graphic_object*)creep2);
	presentRenderer(underLoop);
	deleteRenderer();
    return 0;
}
