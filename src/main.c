#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

#include "map.c"
#include "collision.c"

// This holds the Game Loop, SDL Setup
// TEST FILE
// Final "main" will be in "JustRight.c"
// (CmakeLists.txt will need an update when this happens)

int main(int argc, char* argv[]) {
	printf("Good Compile");

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
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

	printf("Good Initialize\n");

	// Demo Map	
	Map demo = initMap();

	// if (demo.solidTiles[0]) {
	//	printf("Map did not Initialize\n");
	//	SDL_DestroyRenderer(renderer);
	//	SDL_DestroyWindow(window);
        //	SDL_Quit();
	//	exit(1);
	// }

	printf("Good Map Initialize\n");
	

	// Spawn Player Entity
	Entity player = {
		"player1", // id
		SCREEN_WIDTH / 2, // x
		SCREEN_HEIGHT / 2, // y
		16, // width
		16, // height
		0, // VX
		0, // VY
		0, // Facing
		100, // health
		10, // damage
		ENTITY_PLAYER
	};
	printf("Good Entity Spawn\n");

	// Game Loop
	int running = 1;
	SDL_Event event;

	while (running) {
		// printf("Running\n");
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

				case SDL_QUIT: {
					running = 0;
					break;
				}
				case SDL_KEYDOWN: {
					switch (event.key.keysym.sym) {
						case SDLK_w: {
							player.velocityY
							= -PLAYER_SPEED;
							break;
						}
						case SDLK_s: {
							player.velocityY
							= PLAYER_SPEED;
							break;
						}
						case SDLK_a: {
							player.velocityX
							= -PLAYER_SPEED;
							break;
						}
						case SDLK_d: {
							player.velocityX
							= PLAYER_SPEED;
							break;
						}
					}
					break;
				}
				case SDL_KEYUP: {
					switch (event.key.keysym.sym) {
						case SDLK_w: {
							player.velocityY
							= ENTITY_STOP;
							break;
						}
						case SDLK_s: {
							player.velocityY
							= ENTITY_STOP;
							break;
						}
						case SDLK_a: {
							player.velocityX
							= ENTITY_STOP;
							break;
						}
						case SDLK_d: {
							player.velocityX
							= ENTITY_STOP;
							break;
						}
					}
					break;
				}
			}
		}
		
	


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Test Rect
		// SDL_Rect testRect = {100, 100, 250, 250};
		// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		// SDL_RenderFillRect(renderer, &testRect);
		
		// Render Map
		drawMap(renderer, &demo);
		// printf("Good Map Draw\n");	
		
		// Store Old PP (For Collisions)
		int oldX = player.x;
		int oldY = player.y;

		// Update Player Position
		player.x += player.velocityX;
		player.y += player.velocityY;

		// Check Collisions
		if (checkMapCollision(&player, &demo)) {
			printf("Moving Player Back\n");
			player.x = oldX;
			player.y = oldY;
			//player.x += player.velocityX;
			//player.y += player.velocityY;
		}

		// Render Player
		SDL_Rect playerTile = {
			player.x,
			player.y,
			player.width,
			player.height
		};
		// printf("Good Player Render\n");

		const char* sdl_error = SDL_GetError();
		if (sdl_error && sdl_error[0] != '\0') {
			printf("Error Detected: %s\n", sdl_error);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			exit(1);
		}

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &playerTile);
		// printf("Good Player Draw\n");

		// Check Bounding Box
		

		// Update
		SDL_RenderPresent(renderer);
		SDL_Delay(16); // 60 FPS
	}
	
	// Clean
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("Clean Destroy\n");
	return(0);
}
