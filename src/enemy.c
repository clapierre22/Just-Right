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
	enemy->knockback = ENEMY_BASE_KNOCKBACK;
	enemy->attacking = FALSE; // Default is not attacking
	enemy->hit = FALSE;
	enemy->stunTime = ENTITY_STOP;
	enemy->coolTime = PLAYER_SWING_COOL;
	enemy->onCooldown = FALSE;
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
    if (enemy->stunTime > 0) {
        // Knockback active, decrement timer and move by velocity
        // moveEnemy(enemy);
        enemy->stunTime--;
        if (enemy->stunTime == 0) {
            enemy->hit = FALSE;
            enemy->velocityX = 0;
            enemy->velocityY = 0;
        }
    } else {
		// Normal tracking logic
		int dx = player->x - enemy->x;
		int dy = player->y - enemy->y;
		float length = sqrtf(dx * dx + dy * dy);
		if (length > 0) {
			enemy->velocityX = (int)(ENEMY_SPEED * dx / length);
			enemy->velocityY = (int)(ENEMY_SPEED * dy / length);
		} else {
			enemy->velocityX = ENTITY_STOP;
			enemy->velocityY = ENTITY_STOP;
		}

		// Check for collision with player
		if (checkEntityCollision(enemy, player)) {
			enemy->velocityX = ENTITY_STOP;
			enemy->velocityY = ENTITY_STOP;
		}
	}

    moveEnemy(enemy);
}
