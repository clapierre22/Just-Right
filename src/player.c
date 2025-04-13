#include <stdio.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

Entity initPlayer(void);
SDL_Rect drawPlayer(Entity *player);
//void movePlayer(int vX, int vY);

Entity initPlayer(void) {
	// TODO: Correct spawning and drawing of player
	
	Entity player = {
		"player_entity",
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2,
		28,
		32,
		0,
		0,
		0,
		100,
		10,
		ENTITY_PLAYER
	};

	printf("Good Player Spawn\n");

	return player;
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
