// defs.h
#pragma once

// Sceen
#define SCREEN_WIDTH 1360
#define SCREEN_HEIGHT 900

// Map
#define TILE_SIZE 32
#define MAP_WIDTH 33 // 32 (Floor) + 1 (Walls)
#define MAP_HEIGHT 33

// Render
#define RENDER_WIDTH 32
#define RENDER_HEIGHT 32

// Camera
#define MAP_REN_X ((SCREEN_WIDTH - (RENDER_WIDTH * TILE_SIZE)) / 2)
#define MAP_REN_Y ((SCREEN_HEIGHT - (RENDER_HEIGHT * TILE_SIZE)) / 2)

typedef enum {
	ENTITY_PLAYER,
	ENTITY_ENEMY,
	ENTITY_ITEM,
} EntityType;

#define GRAVITY 1
#define JUMP = -12
#define PLAYER_SPEED 4

