#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

//void initCollision(void);
int collision(SDL_Rect a, SDL_Rect b);
int checkMapCollision(Entity *player, Map *map);

//void initCollision(void) {
//	
//}

int collision(SDL_Rect a, SDL_Rect b) {
	int AL, AR, AT, AB;
	int BL, BR, BT, BB;

	// Rect A Left, Right, Top, Bottom
	AL = a.x;
	AR = a.x + a.w;
	AT = a.y;
	AB = a.y + a.h;

	// Rect B Left, Right, Top, Bottom
	BL = b.x;
	BR = b.x + b.w;
	BT = b.y;
	BB = b.y + b.h;

	return !(AL >= BR || AR <= BL || AT >= BB || AB <= BT);
}

int checkMapCollision(Entity *player, Map *map) {
	SDL_Rect playerBox = {
		player->x,
		player->y,
		player->width,
		player->height
	};

	for (int i = 0; i < SOLID_TILES; i++) {
		if (collision(playerBox, map->solidTiles[i])) {
			printf("Collision Detected\n");
			return 1;
		}
	}

	return 0;
}

