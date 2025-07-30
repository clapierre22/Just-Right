// defs.h
#pragma once

// Base
#define TRUE 1
#define FALSE 0

// Sceen
#define SCREEN_WIDTH 1360
#define SCREEN_HEIGHT 768

// Map
// TILE_SIZE ~= 45px
#define TILE_SIZE (SCREEN_HEIGHT/MAP_HEIGHT)
#define MAP_WIDTH 17 // 32 (Floor) + 1 (Walls)
#define MAP_HEIGHT 17
#define MAP_MID_X SCREEN_WIDTH/2
#define MAP_MID_Y SCREEN_HEIGHT/2
#define TOTAL_TILES MAP_WIDTH * MAP_HEIGHT
#define SOLID_TILES (2 * MAP_WIDTH + 2 * (MAP_HEIGHT - 2))
#define SPAWN_TILES TOTAL_TILES/4

// Tile Type
#define GROUND 1
#define WALL 0
#define AIR 2

// Level
#define MAX_ENTITIES 20
#define MAX_PLAYERS 1
#define MAX_ENEMIES MAX_ENTITIES - MAX_PLAYERS
#define MAX_SPAWNS 2
#define MAX_OBJECTIVES 1
#define MAX_POINTS 10
#define ENEMY_ID 64
#define POINT_BASE_INTERVAL 60 // Frames (~1/sec)

typedef enum {
	POINT_UNASSIGNED,
	POINT_SPAWN,
	POINT_GAME,
	POINT_POINT,
} PointType;

typedef enum {
	NOT_SPAWN,
	SPAWN_PLAYER,
	SPAWN_ENEMY,
} SpawnType;

typedef enum {
	POINT_STOP,
	POINT_RUN,
	POINT_PAUSE,
	POINT_ERROR,
} PointStatus;

// Render
#define RENDER_WIDTH 16
#define RENDER_HEIGHT 16

// Camera
#define MAP_REN_X ((SCREEN_WIDTH - (RENDER_WIDTH * TILE_SIZE)) / 2)
#define MAP_REN_Y ((SCREEN_HEIGHT - (RENDER_HEIGHT * TILE_SIZE)) / 2)

#define CAMERA_ZOOM 1.5f

#define CAMERA_WIDTH SCREEN_WIDTH // was 1280, but this would cause popping
#define CAMERA_HEIGHT SCREEN_HEIGHT // was 640, same issue as above

#define CAMERA_START_X SCREEN_WIDTH / 2
#define CAMERA_START_Y SCREEN_HEIGHT / 2

// Mouse
typedef enum {
	MOUSE_PASSIVE,
	MOUSE_ACTIVE,
	MOUSE_REFRESH,
	MOUSE_BLOCKED,
} MouseState;

#define MOUSE_WIDTH 16
#define MOUSE_HEIGHT 16
#define MOUSE_RADIUS 0.5f

// Entity
typedef enum {
	ENTITY_UNASSIGNED,
	ENTITY_PLAYER,
	ENTITY_ENEMY,
	ENTITY_ITEM,
} EntityType;

#define GRAVITY 1
#define JUMP = -12
#define ENTITY_STOP 0
#define POS_MOVE 1
#define NEG_MOVE -1

// Directions
// TODO: Finish implementing directions
#define NORTH (1 << 0) // 0001
#define EAST (1 << 1) // 0010
#define SOUTH (1 << 2) // 0100
#define WEST (1 << 3) // 1000

#define NORTHEAST (NORTH | EAST)
#define SOUTHEAST (SOUTH | EAST)
#define SOUTHWEST (SOUTH | WEST)
#define NORTHWEST (NORTH | WEST)

// Player
#define PLAYER_ONE 0
#define PLAYER_TWO 1
#define PLAYER_THREE 2
#define PLAYER_FOUR 3

#define PLAYER_BASE_X SCREEN_WIDTH/2 - PLAYER_WIDTH/2
#define PLAYER_BASE_Y SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2
#define PLAYER_WIDTH 16
#define PLAYER_HEIGHT 28

#define PLAYER_BASE_HEALTH 100
#define PLAYER_BASE_DAMAGE 5
#define PLAYER_BASE_RANGE 100
#define PLAYER_BASE_KNOCKBACK 10
#define PLAYER_SPEED 4

#define PLAYER_SWING_COOL 60 // Frames, used to calculate swing cooldown for player

#define PADDING 1

// Enemy
#define ENEMY_BASE_HEALTH 10
#define ENEMY_BASE_DAMAGE 10
#define ENEMY_BASE_KNOCKBACK 5 // pxs, used to calculate knockback distance for attackTo
#define ENEMY_SPEED 3

#define BASE_STUN 10 // Frames, used to calculate stun time for attackTo