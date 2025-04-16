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
	player->x = SCREEN_WIDTH/2;
	player->y = SCREEN_WIDTH/2;
	player->width = PLAYER_WIDTH;
	player->height = PLAYER_HEIGHT;
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
		player->width,
		player->height
	};

	return playerTile;
}

//void movePlayer(int vX, int vY) {
	//player
