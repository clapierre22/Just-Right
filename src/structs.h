#pragma once
#include <SDL2/SDL.h>
#include "defs.h"

typedef struct {
	char id[32];
	// SDL_Texture* sprite;
	int x, y, width, height;
	int velocityX, velocityY, facing;
	int health, damage;
	EntityType type;
} Entity;

typedef struct {
	SDL_Window* window;
	Entity player;
	Entity enemy[32];
} Game;

typedef struct {
	int tile;
	int tileType;
	// 1 = Solid, 0 = Passable
	int solid;
} RoomTile;

typedef struct {
	int map[MAP_WIDTH][MAP_HEIGHT];
	SDL_Rect solidTiles[SOLID_TILES];
} Map;

typedef struct {
	SDL_Point renderOffset;
	// Include player entity
	Map room; 
} Level;

