#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

#include "map.c"
#include "collision.c"
#include "player.c"

// This holds the Game Loop, SDL Setup
// TEST FILE
// Final "main" will be in "JustRight.c"
// (CmakeLists.txt will need an update when this happens)

// TODO:
// when colliding with walls at angle, player keeps moving in non wall angle <<
// camera
// enemies
// fighting logic
// spawn logic
// better level sprites
// better entity sprites
// loot logic
// level logic and changing levels (portals?)
// better level design
// ---Split into Chess Game and JR here---
// local second player
// online second player
// gameplay

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
	Entity player = initPlayer();

	printf("Good Entity Spawn\n");

	// Game Loop
	int running = TRUE;
	SDL_Event event;

	while (running) {
		// printf("Running\n");
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

				case SDL_QUIT: {
					running = FALSE;
					break;
				}
				case SDL_KEYDOWN: {
					switch (event.key.keysym.sym) {
						case SDLK_w: {
							player.facing = NORTH;
							player.velocityY = -PLAYER_SPEED;

							break;
						}
						case SDLK_s: {
							player.facing = SOUTH;
							player.velocityY = PLAYER_SPEED;

							break;
						}
						case SDLK_a: {
							player.facing = WEST;
							player.velocityX = -PLAYER_SPEED;

							break;
						}
						case SDLK_d: {
							player.facing = EAST;
							player.velocityX = PLAYER_SPEED;

							break;
						}
					}
					break;
				}
				case SDL_KEYUP: {
					switch (event.key.keysym.sym) {
						case SDLK_w: {
							if (player.velocityY < ENTITY_STOP) {
								player.velocityY = ENTITY_STOP;
							}

							break;
						}
						case SDLK_s: {
							if (player.velocityY > ENTITY_STOP) {
								player.velocityY = ENTITY_STOP;
							}

							break;
						}
						case SDLK_a: {
							if (player.velocityX < ENTITY_STOP) {
								player.velocityX = ENTITY_STOP;
							}

							break;
						}
						case SDLK_d: {
							if (player.velocityX > ENTITY_STOP) {
								player.velocityX = ENTITY_STOP;
							}
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
		
		// Store Old Player Position (For Collisions)
		int oldX = player.x;
		int oldY = player.y;

		// Move to new Player X Position
		player.x += player.velocityX;
		
		// Check X Collision
		if (checkMapCollision(&player, &demo, player.velocityX > 0 ? EAST : WEST)) {
			printf("Moving Player Back, X axis\n");
			player.x = oldX;
			player.velocityX = ENTITY_STOP;
			//player.x += player.velocityX;
			//player.y += player.velocityY;
		}
		
		// Move to new Player Y Position
		player.y += player.velocityY;

		// Check Y Collision
		if (checkMapCollision(&player, &demo, player.velocityY > 0 ? SOUTH : NORTH)) {
			printf("Moving Player Back, Y axis\n");
			player.y = oldY;
			player.velocityY = ENTITY_STOP;
		}

		// Check Diagonal (X + Y) Collision
		// TODO

		// Debug Collisions
		//if (checkMapCollisionDebug(renderer, &player, &demo)) {
		//	printf("Moving Player Back\n");
		//	player.x = oldX;
		//	player.y = oldY;
		//}

		// Render Player
		SDL_Rect playerTile = drawPlayer(&player);
		
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
