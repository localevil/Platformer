#include <stdio.h>

#include "collision.h"
#include "renderer.h"
#include "player.h"

static player_t pl = {0};

void underLoop()
{
    static int count = 0;
    pl.textX = count * pl.height;
    if (count < 3)
        count++;
    else
        count = 0;
    pl.x = pl.x + pl.vel;
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
    pl.vel = 3;
	addObject((struct grafic_object*)&pl);
	presentRenderer(underLoop);
	deleteRenderer();
    return 0;
}
