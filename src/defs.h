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
#define SOLID_TILES (2 * MAP_WIDTH + 2 * (MAP_HEIGHT - 2))

// Tile Type
#define GROUND 1
#define WALL 0
#define AIR -1

// Render
#define RENDER_WIDTH 16
#define RENDER_HEIGHT 16

// Camera
#define MAP_REN_X ((SCREEN_WIDTH - (RENDER_WIDTH * TILE_SIZE)) / 2)
#define MAP_REN_Y ((SCREEN_HEIGHT - (RENDER_HEIGHT * TILE_SIZE)) / 2)

// Entity
typedef enum {
	ENTITY_PLAYER,
	ENTITY_ENEMY,
	ENTITY_ITEM,
} EntityType;

#define GRAVITY 1
#define JUMP = -12
#define ENTITY_STOP 0

// Directions
// TODO: Finish implementing directions
#define NORTH 0000
#define NORTHEAST 0001 
#define EAST 0011
#define SOUTHEAST 0111
#define SOUTH 1111
#define SOUTHWEST 1110
#define WEST 1100
#define NORTHWEST 1000

// Player
#define PLAYER_BASE_HEALTH 100
#define PLAYER_BASE_DAMAGE 10
#define PLAYER_SPEED 4
#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 28

