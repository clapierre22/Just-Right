#include "spawn.h"

void spawnPlayer(Map *map) {
	// TODO
	// Creates new player Entity at specified spawn point
}

void spawnEnemy(Level *level) {
	// TODO
	// Creates new enemy Entity at random map spawn point x,y
	// Add new Entity to map list
	//
	// REWORK
	// Roll random offset float between -1, 1
	// multiply map mid point x,y by offset float
	// spawn enemy entity at that value
	//
	// The reason I tried the tile thing is to prevent spawning on top of player
	// instead, a checker can check if the player is within a specific rage, then try new spawn
	//	

	
	int randomIndex = rand() % SPAWN_TILES;
	// Check for player collison here, if invalid x,y then reroll the random value
	// REMINDER: remove the spawn tiles from defs.h and structs.h and level files
	SDL_Rect spawnPoint = {
		// midpoint x * offset
		// midpoint y * offset
		// Red, Square
		MAP_MID_X * offset,
		MAP_MID_Y * offset,
		PLAYER_WIDTH,
		PLAYER_HEIGHT
	};

	//static int enemyCount = 0;

	Entity enemy = initEnemy();
	char enemyID[ENEMY_ID];

	snprintf(
		enemyId, 
		sizeof(enemyId), 
		"enemy_entity_%d", 
		enemyCount++);
	strcpy(enemy.id, enemyId);

	enemy.x = spawnPoint.x - enemy.w / 2;
	enemy.y = spawnPoint.y - enemy.h / 2;

	level->enemies[enemyCount] = enemy;

	// Remove spawn tile from map list of spawn tiles

}
