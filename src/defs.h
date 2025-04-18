// defs.h
#pragma once

// Sceen
#define SCREEN_WIDTH 1360
#define SCREEN_HEIGHT 768

// Map
// TILE_SIZE ~= 45px
#define TILE_SIZE (SCREEN_HEIGHT/MAP_HEIGHT)
#define MAP_WIDTH 17 // 32 (Floor) + 1 (Walls)
#define MAP_HEIGHT 17

#define GROUND 1
#define WALL 0
#define AIR -1

// Render
#define RENDER_WIDTH 16
#define RENDER_HEIGHT 16
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

