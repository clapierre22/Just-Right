#pragma once
#include <SDL2/SDL.h>
#include "defs.h"

typedef struct {
	char id[32];
	// SDL_Texture* sprite;
	// TODO: Change all instances of "width, height" with 'w, h'
	int x, y, w, h;
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
	int x, y;
	int w, h;
} Camera;

typedef struct {
	SDL_Point renderOffset;
	// Include player entity
	Map room; 
} Level;

