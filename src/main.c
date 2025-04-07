#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

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
		return 1;
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
		return 1;
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
		return 1;
	}

	// Game Loop
	bool running = true;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Test Rect
		SDL_Rect testRect = {100, 100, 250, 250};
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &testRect);

		// Update
		SDL_RenderPresent(renderer);
	}

	// Clean
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return(0);
}
