#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

Map initMap(void);
// static void loadTiles(void);
static void loadMap(Map* map);
void drawMap(SDL_Renderer* renderer, Map* map);

Map initMap(void) {

	// memset(&level.map, 0, sizeof(int) * MAP_WIDTH * MAP_HEIGHT);
	
	Map currentMap;

	loadMap(&currentMap);

	// drawMap();
	
	return currentMap;
}

static void loadMap(Map* map) {
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
		}
	}
}

void drawMap(SDL_Renderer* renderer, Map* map) {

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
					SDL_SetRenderDrawColor(
						renderer,
						100,
						100,
						100,
						255);
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

				SDL_RenderFillRect(renderer, &tile);

				// Outline
				SDL_SetRenderDrawColor(
					renderer,
					50,
					50,
					50,
					255);
				
				SDL_RenderDrawRect(renderer, &tile);
		}
	}
}
