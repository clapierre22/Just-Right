#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

// Set DEBUG to 1 for Debugging Draws of Bounding Boxes
#define DEBUG 0

//void initCollision(SDL_Renderer *renderer);
int collision(SDL_Rect a, SDL_Rect b);
int checkMapCollision(Entity *entity, Map *map);
void collisionDebug(SDL_Renderer *renderer, SDL_Rect a, SDL_Rect b);
int checkMapCollisionDebug(
		SDL_Renderer *renderer, Entity *entity, Map *map);

//void initCollision(SDL_Renderer *renderer, Entity *entity, Map *map) {
	// TODO: Implement to allow checkMapCollision to be called
	// without need to input player, map. Same with collisionDebug
	
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

int checkMapCollision(Entity *entity, Map *map) {
	SDL_Rect entityBox = {
		entity->x,
		entity->y,
		entity->width,
		entity->height
	};

	for (int i = 0; i < SOLID_TILES; i++) {
		if (collision(entityBox, map->solidTiles[i])) {
			printf("Collision Detected\n");
			return 1;
		}
	}

	return 0;
}

// Draws additional outline around the colliding Rectangles
void collisionDebug(SDL_Renderer *renderer, SDL_Rect a, SDL_Rect b) {
	// TODO: Draw outline around both rectangles that are colliding
	SDL_SetRenderDrawColor(
		renderer,
		255,
		0,
		0,
		255);

	SDL_RenderDrawRect(renderer, &a);

	SDL_SetRenderDrawColor(
		renderer,
		0,
		255,
		0,
		255);

	SDL_RenderDrawRect(renderer, &b);
}

int checkMapCollisionDebug(
		SDL_Renderer *renderer, Entity *entity, Map *map) {
	SDL_Rect entityBox = {
		entity->x,
		entity->y,
		entity->width,
		entity->height
	};

	for (int i = 0; i < SOLID_TILES; i++) {
		if (collision(entityBox, map->solidTiles[i])) {
			printf("Collision Detected\n");
			collisionDebug(
					renderer, 
					entityBox, 
					map->solidTiles[i]);
			return 1;
		}
	}

	return 0;
}

	

