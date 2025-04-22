#include "map.h"

static void loadMap(Map *map) {
	// int currentMap.map;
	
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for(int x = 0; x < MAP_WIDTH; x++) {
			// Check Walls
			if (x == 0
				|| y == 0
				|| x == MAP_WIDTH - 1
				|| y == MAP_HEIGHT - 1)
				{ map->map[x][y] = WALL;
			} else {
				map->map[x][y] = GROUND;
			}
			
			// Add all Walls to solidTiles

		}
	}
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

	int i = 0;

	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			SDL_Rect tile = {
				MAP_REN_X + (x * TILE_SIZE),
				MAP_REN_Y + (y * TILE_SIZE),
				TILE_SIZE,
				TILE_SIZE
			};

			switch(map->map[x][y]) {
				case WALL: {
					if (i >= SOLID_TILES) printf("ERROR, OOB\n");

					SDL_SetRenderDrawColor(
						renderer,
						100,
						100,
						100,
						255);
					map->solidTiles[i] = tile;
					i++;
					//printf("Map Tile (%d, %d) listed as Solid Tile\n", x, y);
					break;
				} case GROUND: {
					SDL_SetRenderDrawColor(
						renderer,
						200,
						200,
						100,
						255);
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
			
			// PROBLEM: withinCamera takes Camera, Entity
			if (withinCameraTile(camera, &tile)) {
				// If within Camera, then draw Tile
				SDL_RenderFillRect(renderer, &tile);

				// Outline
				SDL_SetRenderDrawColor(
					renderer,
					50,
					50,
					50,
					255
				);
					
				SDL_RenderDrawRect(renderer, &tile);
			}

			
		}
	}
}
