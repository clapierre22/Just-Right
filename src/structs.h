#pragma once
#include <SDL2/SDL.h>
#include "defs.h"

typedef struct {
	char id[32];
	SDL_Texture* sprite;
	int x, y, width, height;
	int velocityX, velocityY, facing;
	int health, damage;
	EntityType type;
	bool onGround;
} Entity;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Entity player;
	Entity enemy[32];
} Game;

typedef struct {
	int tile;
	int visible;
	int revealed;
} RoomTile;

typedef struct {
	int entityId;
	// Includes player entity
	RoomTile map[MAP_WIDTH][MAP_HEIGHT];
	SDL_Point camera;
} Level;

