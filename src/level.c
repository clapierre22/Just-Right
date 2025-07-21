#include "level.h"
	
// Data and logical operations of the map, entities
// Take in the map information, point information, and entity information to run game logic

Level initLevel(void) {
	// initLevel generates the player, enemies, map; holds within the level object
	Level level;

	loadLevel(&level);
	printf("Good Level Init\n");

	return level;
}

void loadLevel(Level *level) {
	// loads level information
	level->map = initMap();
	level->camera = initCamera();
	level->players = malloc(sizeof(Entity) * MAX_PLAYERS);
	level->enemies = malloc(sizeof(Entity) * MAX_ENEMIES);
	level->spawns = malloc(sizeof(Point) * 1);
	level->objectives = malloc(sizeof(Point) * 1);
	level->points = malloc(sizeof(Point) * 1);

	// example points for testing
	level->spawns[0] = initPoint();
	level->objectives[0] = initPoint();
	level->points[0] = initPoint();
	level->spawnCount = 1;
	level->objectiveCount = 1;
	level->pointCount = 1;

	changePoint(&level->spawns[0], POINT_SPAWN, SPAWN_ENEMY);
	changePoint(&level->objectives[0], POINT_GAME, NOT_SPAWN);
	changePoint(&level->points[0], POINT_POINT, NOT_SPAWN);

	movePoint(&level->points[0], MAP_MID_X + TILE_SIZE, MAP_MID_Y + TILE_SIZE);
	movePoint(&level->objectives[0], MAP_MID_X - TILE_SIZE, MAP_MID_Y - TILE_SIZE);
	movePoint(&level->spawns[0], MAP_MID_X + (2 * TILE_SIZE), MAP_MID_Y + (2 * TILE_SIZE));

	if (!level->players || !level->enemies || !level->points) {
		printf("Failed to allocate memory\n");
		exit(0);
	}
}

void spawnEntities(Level *level) {
	// placeholder for spawn and spawnpoint logic

	// Reset counter
	level->playerCount = 0;
	level->enemyCount = 0;

	// single player
	level->players[PLAYER_ONE] = initPlayer();
	level->playerCount++;
	printf("Good Player Spawn\n");
    
	// enemies
    do {
		activatePoint(&level->spawns[0], level);
    } while (level->enemyCount < MAX_ENEMIES);
}

void changeMap(Level *level, Map *map) {
	// changes map (default map is current demo square)
}

void updateLevel(Level *level) {
	// runs the update function on all Entities, points
	if (level->players) {
		for (int p = PLAYER_ONE; p < MAX_PLAYERS; p++) {
			updatePlayer(&level->players[p], &level->map);
		}
		level->players[PLAYER_ONE].coolTime--;
	}
	if (level->enemies) {
		for (int e = 0; e < level->enemyCount; e++) {
			updateEnemy(&level->enemies[e], &level->players[PLAYER_ONE]); // single player
		}
	}
	if (level->players 
		&& level->enemies 
		&& level->players[PLAYER_ONE].attacking) {
			for (int i = level->enemyCount - 1; i >= 0; i--) {
				calculateFight(&level->players[PLAYER_ONE], &level->enemies[i]);
				if (level->enemies[i].health <= 0) {
					printf("Enemy %d removed, new enemy count: %d\n", level->enemies[i].id, level->enemyCount - 1);
					if (i != level->enemyCount - 1) {
						level->enemies[i] = level->enemies[level->enemyCount - 1];
					}
					level->enemyCount--;

					continue;
				}
			}

			// Save space when large ammounts die
			if (level->enemyCount == MAX_ENEMIES / 2) {
				Entity *temp = realloc(level->enemies, level->enemyCount * sizeof(Entity));
				if (temp) {
					level->enemies = temp;  // Use the new memory block
					printf("Successful realloc\n");
				} else {
					// realloc failed (keep using the old block)
					fprintf(stderr, "Failed to shrink enemy array\n");
				}
			}
			
			level->players[PLAYER_ONE].attacking = FALSE;
	}

	// level->players[PLAYER_ONE].coolTime--;

	moveCamera(&level->camera, &level->players[PLAYER_ONE]);
}

void renderLevel(Level *level, SDL_Renderer *renderer) {
	// renders the level, entities, points
	// Order: Map, Points, Enemies, Players
	drawMap(renderer, &level->camera, &level->map);
	if (level->spawns) {
		for (int s = 0; s < level->spawnCount; s++) {
			renderPoint(renderer, &level->camera, &level->spawns[s]);
		}
	}
	if (level->objectives) {
		for (int o = 0; o < level->objectiveCount; o++) {
			renderPoint(renderer, &level->camera, &level->objectives[o]);
		}
	}
	if (level->points) {
		for (int t = 0; t < level->pointCount; t++) {
			renderPoint(renderer, &level->camera, &level->points[t]);
		}
	}
	if (level->enemies) {
		for (int e = 0; e < level->enemyCount; e++) {
			renderEntity(renderer, &level->camera, &level->enemies[e]);
		}
	}
	if (level->players) {
		for (int p = 0; p < level->playerCount; p++) {
			renderEntity(renderer, &level->camera, &level->players[p]);
		}
	}
}

void destroyLevel(Level *level) {
	if (!level) return;

	if (level->spawns) {
		free(level->spawns);
	}

	if (level->objectives) {
		free(level->objectives);
	}

	if (level->points) {
		free(level->points);
	}

	if (level->players) {
		free(level->players);
	}

	if (level->enemies) {
		free(level->enemies);
	}
}