#include "main.h"

// This holds the Game Loop, SDL Setup
// TEST FILE
// Final "main" will be in "JustRight.c"
// (CmakeLists.txt will need an update when this happens)

// TODO:
// camera (works, only render stuff in camera (screen))
// enemies DONE
// // example spawn DONE
// // test following player DONE 
// // check collision between player and enemy DONE
// fighting logic <<
// spawn logic
// ---Split into Chess Game and JR here---
// better level sprites
// better entity sprites
// loot logic
// level logic and changing levels (portals?)
// better level design
// local second player
// online second player
// gameplay

int main(int argc, char* argv[]) {
	printf("Good Build Compile\n");

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
	printf("Good Map Initialize\n");
	
	// Spawn Player Entity
	Entity player = initPlayer();
	printf("Good Entity Spawn\n");

	//Spawn Enemy Entities
	Entity enemy = initEnemy();
	printf("Good Enemy Spawn\n");

	// Initizalize Camera
	Camera camera = initCamera();
	printf("Good Camera Init\n");

	// Game Loop
	int running = TRUE;
	SDL_Event event;

	while (running) {
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
						case SDLK_e: {
							player.attacking = TRUE;

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
						case SDLK_e: {
							player.attacking = FALSE;

							break;
						}
					}
					break;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		drawMap(renderer, &camera, &demo);

		// UPDATES // 

		// Update player 
		updatePlayer(&player, &demo);
	
		// Move Camera to Player Center
		moveCamera(&camera, &player);

		// Update enemies with players current location
		updateEnemy(&enemy, &player);

		// Render Player, Only when within Camera
		// TODO: For loop for each entity (seperate loops for entity, object)
		// 	Camera is called, camera.c add withinCamera (int bool)
		// 	If withinCamera, call render on that Entity
		
		// Move SDL_Renderer init and render func to new file renderHelper.c/.h
		renderEntity(renderer, &camera, &player);

		// printf("Good Player Render\n");
		
		// Render Entities
		//testEnemy.render(renderer, camera.x, camera.y);
		renderEntity(renderer, &camera, &enemy);

		// Render Objects
		//testObject.render(renderer, camera.x, camera.y);

		// Check Fighting
		if (player.attacking) {
			calculateFight(&player, &enemy);
		}

		// Update
		SDL_RenderPresent(renderer);
		SDL_Delay(16); // 60 FPS
	}
	
	// CLEAN //

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("Clean Destroy\n");

	// EXIT //

	return(0);
}
