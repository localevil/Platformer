#include <stdio.h>

#include "collision.h"
#include "renderer.h"
#include "player.h"

void underLoop()
{
	
}


int main()
{
	player_t pl = createPlayer();
	int charTextId = addTexture("characters.png");
	pl.textId = charTextId;
	pl.textX = 0;
	pl.textY = 0;
	pl.width = 32;
	pl.height = 32;
	pl.x = 10;
	pl.y = 10;
	addObject((struct grafic_object*)&pl);
	initRenderer();
	presentRenderer(underLoop);
	deleteRenderer();
    return 0;
}
