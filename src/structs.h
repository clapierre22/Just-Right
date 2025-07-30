#pragma once
#include <SDL2/SDL.h>
#include "defs.h"

typedef struct {
	int id;
	// SDL_Texture* sprite;
	int x, y, w, h;
	int velocityX, velocityY, facing;
	int inputX, inputY;
	int health, damage, knockback;
	int attacking, hit;
	int stunTime, coolTime;
	int onCooldown;
	EntityType type;
} Entity;

typedef struct {
	int x, y;
	int w, h;
	float r;
	MouseState state;
} Mouse;

typedef struct {
	SDL_Window *window;
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
	// TODO: Change x,y to float
	int x, y;
	int w, h;
	float zoom;
} Camera;

typedef struct {
	int x, y;
} Location;

typedef struct {
	int id;
	int x, y;
	int w, h;
	PointType type;
	SpawnType spawn;
	PointStatus status;
	int interval;
	SDL_Rect hitBox;
} Point;

typedef struct {
	Map map; 
	Camera camera;
	Mouse mouse;
	Entity *entities;
	Point *spawns;
	Point *objectives;
	Point *points;
	int entityCount, playerCount, enemyCount, spawnCount, objectiveCount, pointCount;
} Level;
