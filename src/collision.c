#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

// Set DEBUG to 1 for Debugging Draws of Bounding Boxes
#define DEBUG 0

//void initCollision(SDL_Renderer *renderer);
int collision(SDL_Rect a, SDL_Rect b);
int checkMapCollision(Entity *entity, Map *map, int direction);
int collisionNorth(SDL_Rect a, SDL_Rect b);
int collisionEast(SDL_Rect a, SDL_Rect b);
int collisionSouth(SDL_Rect a, SDL_Rect b);
int collisionWest(SDL_Rect a, SDL_Rect b);
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

int checkMapCollision(Entity *entity, Map *map, int direction) {

	SDL_Rect entityBox = {
		entity->x,
		entity->y,
		entity->width,
		entity->height
	};
	
	switch (direction) { 
		case NORTH: {
			entityBox.y -= PADDING;
			entityBox.h += PADDING;

			break;
		}
		case EAST: {
			entityBox.w += PADDING;

			break;
		}
		case SOUTH: {
			entityBox.h += PADDING;

			break;
		}
		case WEST: {
			entityBox.x -= PADDING;
			entityBox.w += PADDING;

			break;
		}
	}

	for (int i = 0; i < SOLID_TILES; i++) {
		if (collision(entityBox, map->solidTiles[i])) {
			return TRUE;
		}
	}

	return FALSE;
}

int collisionNorth(SDL_Rect a, SDL_Rect b) {
	// Returns 1 (True) when Entity North is touching Map South
	// Entity = a, Map = b
	// "If there is a collision to the North..."
	
	//int AT;
	//int BB;

	// Rect A Top
	//AT = a.y;

	// Rect B Bottom
	//BB = b.y + b.h;

	return (a.y < b.y + b.h && a.y + a.h > b.y + b.h && 
            a.x < b.x + b.w && a.x + a.w > b.x);		
}

int collisionEast(SDL_Rect a, SDL_Rect b) {
	// Returns 1 (True) when Entity East is touching Map West
	// Entity = a, Map = b
	// "If there is a collision to the East..."
	
	//int AR;
	//int BL;

	// Rect A Right
	//AR = a.x + a.w;

	// Rect B Left
	//BL = b.x;

	return (a.x + a.w > b.x && a.x < b.x && 
            a.y < b.y + b.h && a.y + a.h > b.y);	
}

int collisionSouth(SDL_Rect a, SDL_Rect b) {
	// Returns 1 (True) when Entity South is touching Map North
	// Entity = a, Map = b
	// "If there is a collision to the South..."
	
	//int AB;
	//int BT;

	// Rect A Top
	//AB = a.y + a.h;

	// Rect B Bottom
	//BT = b.y;

	return (a.y + a.h > b.y && a.y < b.y && 
            a.x < b.x + b.w && a.x + a.w > b.x);
}

int collisionWest(SDL_Rect a, SDL_Rect b) {
	// Returns 1 (True) when Entity West is touching Map East
	// Entity = a, Map = b
	// "If there is a collision to the West..."
	
	//int AL;
	//int BR;

	// Rect A Left
	//AL = a.x;

	// Rect B Right
	//BR = b.x + b.w;

	return (a.x < b.x + b.w && a.x + a.w > b.x + b.w && 
            a.y < b.y + b.h && a.y + a.h > b.y);
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

//SDL_Rect futureBox
	

