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
// level development DONE
	// make specified level.c file DONE
	// transfer all level related logic to level.c, remove from main.c DONE
// spawn logic << 
	// specified entity spawn point that can be set to spawn any entity DONE
	// points objects
		// choose spawn point location DONE
		// can spawn any entity DONE
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
// mouse implementation
	// mouse reports location
	// draw clicker at mouse position
	// accept inputs when clicking the mouse
	// distinguish between left click and right click
	// attack with mouse instead of e key
// map editor
	// map system update
		// divide into maps (cosmetic) and rooms (data, like enemies and logic)
			// OPTIONAL: allow maps to be non square (only reason to not do this is for map bounds are square)
		// allow for premade files to be used to load premade maps
	// interface that allows for easy map creations
		// can use the mouse
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
							level.entities[PLAYER_ONE].facing = NORTH;
							// level.entities[PLAYER_ONE].velocityY = -PLAYER_SPEED;
							level.entities[PLAYER_ONE].inputY = NEG_MOVE;

							break;
						}
						case SDLK_s: {
							level.entities[PLAYER_ONE].facing = SOUTH;
							// level.entities[PLAYER_ONE].velocityY = PLAYER_SPEED;
							level.entities[PLAYER_ONE].inputY = POS_MOVE;

							break;
						}
						case SDLK_a: {
							level.entities[PLAYER_ONE].facing = WEST;
							// level.entities[PLAYER_ONE].velocityX = -PLAYER_SPEED;
							level.entities[PLAYER_ONE].inputX = NEG_MOVE;

							break;
						}
						case SDLK_d: {
							level.entities[PLAYER_ONE].facing = EAST;
							// level.entities[PLAYER_ONE].velocityX = PLAYER_SPEED;
							level.entities[PLAYER_ONE].inputX = POS_MOVE;

							break;
						}
						case SDLK_e: {
							// Cooldown logic for player
							if (!event.key.repeat) {
								if (level.entities[PLAYER_ONE].coolTime <= 0) {
									level.entities[PLAYER_ONE].attacking = TRUE;
									level.entities[PLAYER_ONE].onCooldown = TRUE;
									level.entities[PLAYER_ONE].coolTime = PLAYER_SWING_COOL;
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
							if (level.entities[PLAYER_ONE].inputY < ENTITY_STOP) {
								level.entities[PLAYER_ONE].inputY = ENTITY_STOP;
							}

							break;
						}
						case SDLK_s: {
							if (level.entities[PLAYER_ONE].inputY > ENTITY_STOP) {
								level.entities[PLAYER_ONE].inputY = ENTITY_STOP;
							}

							break;
						}
						case SDLK_a: {
							if (level.entities[PLAYER_ONE].inputX < ENTITY_STOP) {
								level.entities[PLAYER_ONE].inputX = ENTITY_STOP;
							}

							break;
						}
						case SDLK_d: {
							if (level.entities[PLAYER_ONE].inputX > ENTITY_STOP) {
								level.entities[PLAYER_ONE].inputX = ENTITY_STOP;
							}
							break;
						}
						case SDLK_e: {
							level.entities[PLAYER_ONE].attacking = FALSE;
							level.entities[PLAYER_ONE].onCooldown = FALSE;

							break;
						}
					}
					break;
				}
			}
		}

		level.entities[PLAYER_ONE].velocityX = level.entities[PLAYER_ONE].inputX * PLAYER_SPEED;
    	level.entities[PLAYER_ONE].velocityY = level.entities[PLAYER_ONE].inputY * PLAYER_SPEED;

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
