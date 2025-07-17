#include "collision.h"

//void initCollision(SDL_Renderer *renderer);

//int collisionNorth(SDL_Rect a, SDL_Rect b);
//int collisionEast(SDL_Rect a, SDL_Rect b);
//int collisionSouth(SDL_Rect a, SDL_Rect b);
//int collisionWest(SDL_Rect a, SDL_Rect b);

//int checkMapCollisionDebug(SDL_Renderer *renderer, Entity *entity, Map *map);

//void initCollision(SDL_Renderer *renderer, Entity *entity, Map *map) {
	// TODO: Implement to allow checkMapCollision to be called
	// without need to input player, map. Same with collisionDebug
	
//}

int collision(SDL_Rect a, SDL_Rect b) {
	// Detect whether SDL_Rect a and SDL_Rect b are "touching" (position of one or more rect side on both rects have the same coordinate value)
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
	// Using collision(SDL_Rect a, SDL_Rect b); detect if entity collides with a wall/boundary
	SDL_Rect entityBox = {
		entity->x,
		entity->y,
		entity->w,
		entity->h
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

int checkEntityCollision(Entity *a, Entity *b){
	SDL_Rect aBox = {
		a->x,
		a->y,
		a->w,
		a->h
	};

	SDL_Rect bBox = {
		b->x,
		b->y,
		b->w,
		b->h
	};

	return collision(aBox, bBox);
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
