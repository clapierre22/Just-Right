#include "player.h"

//void movePlayer(int vX, int vY);

Entity initPlayer(void) {
	// TODO: Correct spawning and drawing of player
	
	Entity player;

	loadPlayer(&player);
	printf("Good Player Load\n");

	return player;
}

void loadPlayer(Entity *player) {
	// TODO: Add spawn input as parameters taken by initPlayer
	strcpy(player->id, "player_entity");
	player->x = PLAYER_BASE_X;
	player->y = PLAYER_BASE_Y;
	player->w = PLAYER_WIDTH;
	player->h = PLAYER_HEIGHT;
	player->velocityX = ENTITY_STOP;
	player->velocityY = ENTITY_STOP;
	player->facing = NORTH; // TODO: Finish implementing binary for directions
	player->health = PLAYER_BASE_HEALTH;
	player->damage = PLAYER_BASE_DAMAGE;
	player->type = ENTITY_PLAYER;
}

SDL_Rect drawPlayer(Entity *player) {
	SDL_Rect playerTile = {
		player->x,
		player->y,
		player->w,
		player->h
	};

	return playerTile;
}

void movePlayer(Entity *player) {
	player->x += player->velocityX;
	player->y += player->velocityY;
}

void updatePlayer(Entity *player, Map *map) {
	// Checks player position, updates player position based on velocity, cehcks for collisions	
	// Check X Collision
	if (checkMapCollision(player, map, player->velocityX > 0 ? EAST : WEST)) {
		printf("Moving Player Back, X axis\n");
		player->velocityX = ENTITY_STOP;
	}

	// Check Y Collision
	if (checkMapCollision(player, map, player->velocityY > 0 ? SOUTH : NORTH)) {
		printf("Moving Player Back, Y axis\n");
		player->velocityY = ENTITY_STOP;
	}

	// Update player position based on velocity
	// player->x += player->velocityX;
	// player->y += player->velocityY;

	movePlayer(player);
}
