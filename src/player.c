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
	player->knockback = PLAYER_BASE_KNOCKBACK;
	player->attacking = FALSE; // Defualt is not attacking
	player->hit = FALSE;
	player->stunTime = ENTITY_STOP;
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
    // Move X axis and check collision
    player->x += player->velocityX;
    if (checkMapCollision(player, map, player->velocityX > 0 ? EAST : WEST)) {
        // Undo X movement if collided
        player->x -= player->velocityX;
        player->velocityX = ENTITY_STOP;
    }

    // Move Y axis and check collision
    player->y += player->velocityY;
    if (checkMapCollision(player, map, player->velocityY > 0 ? SOUTH : NORTH)) {
        // Undo Y movement if collided
        player->y -= player->velocityY;
        player->velocityY = ENTITY_STOP;
    }
}
