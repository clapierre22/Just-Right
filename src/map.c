#include "map.h"

static void loadMap(Map *map) {
	// int currentMap.map;
	
	int i = 0; // for WALL
	int j = 0; // for SPAWN

	for (int y = 0; y < MAP_HEIGHT; y++) {
		for(int x = 0; x < MAP_WIDTH; x++) {
			RoomTile *tile = malloc(sizeof(RoomTile));
			
			SDL_Rect tileRect = {
				MAP_REN_X + (x * TILE_SIZE),
				MAP_REN_Y + (y * TILE_SIZE),
				TILE_SIZE,
				TILE_SIZE
			};
			
			tile->tileBounds = tileRect;
			// Check Walls
			if (x == 0
				|| y == 0
				|| x == MAP_WIDTH - 1
				|| y == MAP_HEIGHT - 1) {
				tile->tileType = WALL;
				if (i >= SOLID_TILES) printf("ERROR, OOB\n");
				map->solidTiles[i] = tile->tileBounds;
				i++;
			} else {
				int rValue = rand() % (RAND_TOP - 1);
				if (j < SPAWN_TILES && rValue == 0) {
					tile->spawn = 1;
					map->spawnTiles[j] = tile->tileBounds;
					j++;
				}
				tile->tileType = GROUND;
			}

			map->map[x][y] = *tile;
			
			// Add all Walls to solidTiles

		}
	}
	// Below needs too be set so it only happens once
	// Change it so the RoomTile objects are what are being put in the map, not WALL, GROUND
	// 	-> This would require drawMap() to read switch(map->map[x][y].tileType)
}

Map initMap(void) {

	// memset(&level.map, 0, sizeof(int) * MAP_WIDTH * MAP_HEIGHT);
	
	// Make this dyanmically allocated - now declared in map struct
	// SDL_Rect solidTiles[SOLID_TILES];
	
	Map currentMap;

	loadMap(&currentMap);
	printf("Good Map Load\n");

	// drawMap();

	return currentMap;
}

void drawMap(SDL_Renderer *renderer, Camera *camera, Map *map) {
	// TODO: Add another attribute "Spawn Tile" to RoomTile
	// 	-> Make the Spawn attribute random, ~20% chance per tile
	// 	-> -> Add Random

	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
		

			switch(map->map[x][y].tileType) {
				case WALL: {
					SDL_SetRenderDrawColor(
						renderer,
						100,
						100,
						100,
						255);
					// Just changed this to hold RoomTiles instead of SDL_Rect objects
					//printf("Map Tile (%d, %d) listed as Solid Tile\n", x, y);
					break;
				} case GROUND: {
					if (map->map[x][y].spawn) {
						SDL_SetRenderDrawColor(
							renderer,
							255,
							0,
							0,
							255);
					} else {
						SDL_SetRenderDrawColor(
							renderer,
							200,
							200,
							100,
							255);
					}
					break;
				} default: {
					SDL_SetRenderDrawColor(
						renderer,
						0,
						0,
						200,
						255);
					break;
				}
			}
				
			//printf("Drawing Tile at (%d, %d)\n", x, y);
			
			// PROBLEM: Even when should be True, is False (Black Screen)
			renderTile(renderer, camera, &map->map[x][y]);
			
		}
	}
}
