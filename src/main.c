#include "main.h"

// This holds the Game Loop, SDL Setup
// TEST FILE
// Final "main" will be in "JustRight.c"
// (CmakeLists.txt will need an update when this happens)

// TODO:
// camera (works, only render stuff in camera (screen))
// enemies DONE
	// example spawn DONE
	// test following player DONE 
	// check collision between player and enemy DONE
// fighting logic DONE
	// hit detection DONE
	// knockback logic DONE
	// swing cooldown DONE
	// kill enemies DONE
	// adjust player attack range (increase) DONE
// level development <<
	// make specified level.c file
	// transfer all level related logic to level.c, remove from main.c
// spawn logic
	// specified entity spawn point that can be set to spawn any entity
		// choose spawn point location
		// can spawn any entity
		// choose enemy to spawn
			// UPDATE: combine player.c and enemy.c into entity.c, use switch to determine user
			// enemy spawn point
			// player spawn point
		// set respawn timer
		// create tag that turns spawn point on/off, with on continously spawning enemies at set respawn timer
		// collision check to make sure enemies don't spawn on top of player
	// spawn master system that controls the spawn points
		// allows for altering all points at once
		// indirectly allows for different gamemodes to be formed 
		// control all spawn point locations
// map editor
	// map system update
		// divide into maps (cosmetic) and rooms (data, like enemies and logic)
			// OPTIONAL: allow maps to be non square (only reason to not do this is for map bounds are square)
		// allow for premade files to be used to load premade maps
	// interface that allows for easy map creations
		// visual placement editor that allows for non hardcoded designing
		// save maps as file that can then be later run
		// test maps within editor
		
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
	// Enemy data, move to map file
	// Example array of enemies
	Entity *enemies = malloc(sizeof(Entity) * MAX_ENEMIES);
	int enemyCount = 0;
	do {
		enemies[enemyCount] = initEnemy();
		enemies[enemyCount].x = rand() % (SCREEN_WIDTH - PLAYER_WIDTH);
		enemies[enemyCount].y = rand() % (SCREEN_HEIGHT - PLAYER_HEIGHT);
		enemies[enemyCount].id = enemyCount + 1;
		printf("Good enemy spawn, ID: %d\n", enemies[enemyCount].id);
		enemyCount++;
	} while(enemyCount < MAX_ENEMIES);
	// Entity enemy = initEnemy();
	// printf("Good Example Enemy Spawn\n");

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
							// Cooldown logic for player
							if (!event.key.repeat) {
								if (player.coolTime <= 0) {
									player.attacking = TRUE;
									player.onCooldown = TRUE;
									player.coolTime = PLAYER_SWING_COOL;
								} else {
									printf("Player is on cooldown, cannot attack\n");
								}
							}

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
							player.onCooldown = FALSE;

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
		player.coolTime--;
	
		// Move Camera to Player Center
		moveCamera(&camera, &player);

		// Update enemies with players current location
		// updateEnemy(&enemy, &player);

		for (int i = 0; i < enemyCount; i++) {
			updateEnemy(&enemies[i], &player);
			renderEntity(renderer, &camera, &enemies[i]);
		}

		// Render Player, Only when within Camera
		// TODO: For loop for each entity (seperate loops for entity, object)
		// 	Camera is called, camera.c add withinCamera (int bool)
		// 	If withinCamera, call render on that Entity
		
		// Move SDL_Renderer init and render func to new file renderHelper.c/.h
		renderEntity(renderer, &camera, &player);

		// printf("Good Player Render\n");
		
		// Render Entities
		//testEnemy.render(renderer, camera.x, camera.y);
		// renderEntity(renderer, &camera, &enemy);

		// Render Objects
		//testObject.render(renderer, camera.x, camera.y);

		// Check Fighting
		if (player.attacking) {
			for (int i = enemyCount - 1; i >= 0; i--) {
				calculateFight(&player, &enemies[i]);
				if (enemies[i].health <= 0) {
					if (i != enemyCount - 1) {
						enemies[i] = enemies[enemyCount - 1];
					}
					enemyCount--;
					printf("Enemy %d removed, new enemy count: %d\n", enemies[i].id, enemyCount);

					continue;
				}
			}

			// Save space when large ammounts die
					if (enemyCount == MAX_ENEMIES / 2) {
						Entity *temp = realloc(enemies, enemyCount * sizeof(Entity));
						if (temp) {
							enemies = temp;  // Use the new memory block
							printf("Successful realloc\n");
						} else {
							// realloc failed (keep using the old block)
							fprintf(stderr, "Failed to shrink enemy array\n");
						}
					}
			
			// calculateFight(&player, &enemy); // Example enemy
			
			player.attacking = FALSE;
		}

		// Update
		SDL_RenderPresent(renderer);
		SDL_Delay(16); // 60 FPS
	}
	
	// CLEAN //

	free(enemies);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("Clean Destroy\n");

	// EXIT //

	return(0);
}
