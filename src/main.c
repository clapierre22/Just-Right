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
	// make specified level.c file DONE
	// transfer all level related logic to level.c, remove from main.c (stuck on unknown type name Camera in structs.h 42)
// spawn logic
	// specified entity spawn point that can be set to spawn any entity
	// points objects
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

	// INITIALIZE SDL //
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		printf("SDL could not initialize, Error: %s\n",
				SDL_GetError());
		exit(1);
	}

	// Create Window //
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

	// Create Renderer //
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

	// INITIALIZE LEVEL // 
	Level level = initLevel();
	spawnEntities(&level); // To be repalce with spawn logic overhaul

	// GAME LOOP //
	int running = TRUE;
	SDL_Event event;

	// USER INPUT //
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
							level.players[PLAYER_ONE].facing = NORTH;
							level.players[PLAYER_ONE].velocityY = -PLAYER_SPEED;

							break;
						}
						case SDLK_s: {
							level.players[PLAYER_ONE].facing = SOUTH;
							level.players[PLAYER_ONE].velocityY = PLAYER_SPEED;

							break;
						}
						case SDLK_a: {
							level.players[PLAYER_ONE].facing = WEST;
							level.players[PLAYER_ONE].velocityX = -PLAYER_SPEED;

							break;
						}
						case SDLK_d: {
							level.players[PLAYER_ONE].facing = EAST;
							level.players[PLAYER_ONE].velocityX = PLAYER_SPEED;

							break;
						}
						case SDLK_e: {
							// Cooldown logic for player
							if (!event.key.repeat) {
								if (level.players[PLAYER_ONE].coolTime <= 0) {
									level.players[PLAYER_ONE].attacking = TRUE;
									level.players[PLAYER_ONE].onCooldown = TRUE;
									level.players[PLAYER_ONE].coolTime = PLAYER_SWING_COOL;
								} else {
									printf("Player %d is on cooldown, cannot attack\n", PLAYER_ONE + 1);
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
							if (level.players[PLAYER_ONE].velocityY < ENTITY_STOP) {
								level.players[PLAYER_ONE].velocityY = ENTITY_STOP;
							}

							break;
						}
						case SDLK_s: {
							if (level.players[PLAYER_ONE].velocityY > ENTITY_STOP) {
								level.players[PLAYER_ONE].velocityY = ENTITY_STOP;
							}

							break;
						}
						case SDLK_a: {
							if (level.players[PLAYER_ONE].velocityX < ENTITY_STOP) {
								level.players[PLAYER_ONE].velocityX = ENTITY_STOP;
							}

							break;
						}
						case SDLK_d: {
							if (level.players[PLAYER_ONE].velocityX > ENTITY_STOP) {
								level.players[PLAYER_ONE].velocityX = ENTITY_STOP;
							}
							break;
						}
						case SDLK_e: {
							level.players[PLAYER_ONE].attacking = FALSE;
							level.players[PLAYER_ONE].onCooldown = FALSE;

							break;
						}
					}
					break;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Background color
		SDL_RenderClear(renderer);

		// UPDATES // 
		updateLevel(&level);
		renderLevel(&level, renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(16); // 60 FPS
	}
	
	// CLEAN //
	destroyLevel(&level);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("Clean Destroy\n");

	// EXIT //
	return(0);
}
