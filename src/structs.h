#pragma once
#include <SDL2/SDL.h>
#include "defs.h"

typedef struct {
	int id;
	// SDL_Texture* sprite;
	int x, y, w, h;
	int velocityX, velocityY, facing;
	int health, damage, knockback;
	int attacking, hit;
	int stunTime, coolTime;
	int onCooldown;
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
	// 1 = Spawn, 0 = Normal
	int spawn;
	// Turn Spawn to Normal when enemy Spawns (prevent stacking)
	SDL_Rect tileBounds;
} RoomTile;

typedef struct {
	RoomTile map[MAP_WIDTH][MAP_HEIGHT];
	SDL_Rect solidTiles[SOLID_TILES];
	SDL_Rect spawnTiles[SPAWN_TILES];
} Map;

typedef struct {
	Map map; 
	Entity player;
	Entity enemies[MAX_ENEMIES];
} Level;

typedef struct {
	// TODO: Change x,y to float
	int x, y;
	int w, h;
	float zoom;
} Camera;

typedef struct {
	int x, y;
} Location;
