#include "enemy.h"

Entity initEnemy(void) {
	Entity enemy;

	loadEnemy(&enemy);
	printf("Good Enemy Load\n");

	return enemy;
}

void spawnEnemy(Entity *enemy, Map *map) {
	// Takes the spawn information from map.c, assigns enemy spawn to that x, y
	// Have this in spawn.c
}

void loadEnemy(Entity *enemy) {
	strcpy(enemy->id, "enemy_entity");
	// Take the x, y values from the valid spawns from map.c
	enemy->w = PLAYER_WIDTH;
	enemy->h = PLAYER_HEIGHT;
	enemy->velocityX = ENTITY_STOP;
	enemy->velocityY = ENTITY_STOP;
	enemy->facing = NORTH;
	enemy->health = ENEMY_BASE_HEALTH;
	enemy->damage = ENEMY_BASE_DAMAGE;
	enemy->attacking = FALSE; // Default is not attacking
	enemy->type = ENTITY_ENEMY;

	// Remove the below line when spawn.c is implemented
	enemy->x = PLAYER_BASE_X + 64;
	enemy->y = PLAYER_BASE_Y + 64;
}

SDL_Rect drawEntity(Entity *enemy, SDL_Renderer *renderer) {
	// Draws a rectangle that represents enemy hitbox
	SDL_Rect enemyTile = {
		enemy->x,
		enemy->y,
		enemy->w,
		enemy->h
	};

	return enemyTile;
}

void moveEnemy(Entity *enemy) {
	enemy->x += enemy->velocityX;
	enemy->y += enemy->velocityY;
}

void updateEnemy(Entity *enemy, Entity *player) {
	// Update enemy position based on player position
	// Takes the player information and move the enemy in player direction

	// change enemy velocity to match the value of the difference of the player location and enemy location to a value between 1 and 0 then multiply the value by the enemy speed to make it head twoards the player
	
	// Calculate delta value for direction
	int dx = player->x - enemy->x;
	int dy = player->y - enemy->y;

	// Normalize direction
	float len = sqrtf(dx * dx + dy * dy);
	if (len > 0) {
		// Set enemy velocity to move towards player
		enemy->velocityX = (int)(ENEMY_SPEED * dx / len);
		enemy->velocityY = (int)(ENEMY_SPEED * dy / len);
	} else {
		enemy->velocityX = ENTITY_STOP;
		enemy->velocityY = ENTITY_STOP;
	}

	// Check for collision with player
	if (checkEntityCollision(enemy, player)) {
		enemy->velocityX = ENTITY_STOP;
		enemy->velocityY = ENTITY_STOP;
	}
	
	moveEnemy(enemy);
}
