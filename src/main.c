#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

// This holds the Game Loop, SDL Setup
// TEST FILE
// Final "main" will be in "JustRight.c"
// (CmakeLists.txt will need an update when this happens)


int main(int argc, char* argv[]) {
	printf("Good Compile");

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize, Error: %s\n",
				SDL_GetError());
		exit(1);
	}

	// Create Window
	SDL_Window* window = SDL_CreateWindow("SDL2 Test",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (!window){
		printf("Window did not initialize, Error: %s\n",
				SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	// Create Renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window,
			-1,
			SDL_RENDERER_ACCELERATED);

	if (!renderer) {
		printf("Renderer did not initialize, Error: %s\n",
				SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(1);
	}

	// Demo Map
	int map[MAP_WIDTH][MAP_HEIGHT];

	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			// Walls
			if (x == 0
				|| y == 0
				|| x == MAP_WIDTH - 1
				|| y == MAP_HEIGHT - 1) {
				map[x][y] = WALL;
			} else {
				map[x][y] = GROUND;
			}
		}
	}



	// Game Loop
	int running = 1;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Test Rect
		// SDL_Rect testRect = {100, 100, 250, 250};
		// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		// SDL_RenderFillRect(renderer, &testRect);
		
		// Render Map
		for (int y = 0; y < MAP_HEIGHT; y++) {
			for (int x = 0; x < MAP_WIDTH; x++) {
				SDL_Rect tile = {
					MAP_REN_X + (x * TILE_SIZE),
					MAP_REN_Y + (y * TILE_SIZE),
					TILE_SIZE,
					TILE_SIZE,
				};
				
				switch(map[x][y]) {
					case WALL: {
						SDL_SetRenderDrawColor(
							renderer,
							100,
							100,
							100,
							255);
						break;
					}
					case GROUND: {
						SDL_SetRenderDrawColor(
							renderer,
							200,
							200,
							100,
							255);	
						break;
					}
					default: {
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

		// Update
		SDL_RenderPresent(renderer);
	}

	// Spawn Player Entity
	Entity player = {
		"player1", // id
		100, // x
		100, // y
		100, // width
		100, // height
		0, // VX
		0, // VY
		0, // Facing
		100, // health
		10, // damage
		ENTITY_PLAYER};

	SDL_Rect playerTile = {
		player.x,
		player.y,
		player.width,
		player.height};

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &playerTile);

	// Clean
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return(0);
}
