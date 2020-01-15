#include <stdio.h>

#include "collision.h"
#include "renderer.h"
#include "player.h"
#include "movement.h"

static player_t pl = {0};

void underLoop(const uint8_t *keys)
{
    player_movement((movement_object_t*)&pl, keys);
}


int main()
{
    initRenderer();
    pl = createPlayer();
    int charTextId = addTexture("characters.png");
	pl.textId = charTextId;
    pl.width = 32;
    pl.height = 32;
	pl.textX = 0;
    pl.textY = 2 * pl.width;
    pl.x = 0;
    pl.y = 0;
    pl.vel = 1;
    addObject((struct grafic_object*)&pl);
	presentRenderer(underLoop);
	deleteRenderer();
    return 0;
}
