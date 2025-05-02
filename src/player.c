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

// This should be moved to its own file, still takes in *entity to read the sprite info
void render(SDL_Renderer *renderer, Entity *entity) {
// TODO: Switch to use sprite sheet instead of playerTile (which is for bounding box)
	SDL_Rect playerTile = drawPlayer(entity);
	
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &playerTile);
}

//void movePlayer(int vX, int vY) {
	//player
