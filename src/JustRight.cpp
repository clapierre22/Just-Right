#include "JustRight.h"
#include <iostream>

// JustRight.cpp/.exe holds all game information and deals with visual
// generation as well as running all logic files (~/Systems/) and 
// entity spawns (~/Actors/)
//
// Input is included here
// 
// LM: 3/31/25 - Calvin LaPierre

JustRight::JustRight() :
	window(nullptr),
	renderer(nullptr),
	running(false),
	startTime(0)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init Error: " 
			<< SDL_GetError() << std::endl;
		exit(1);
	}

	// I propose somebody open a window
	window = SDL_CreateWindow("JustRight",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIDTH,
			HEIGHT,
			SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "SDL_CreateWindow Error: "
			<< SDL_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	renderer = SDL_CreateRenderer(window,
			-1,
			SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cerr << "SDL_CreateRenderer Error: "
			<< SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit;
		exit(1);
	}

	running = true;
	startTime = SDL_GetTicks();

}

JustRight::~JustRight() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void JustRight::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		if (event.type == SDL_KEYDOWN 
				&& event.key.keysym.sym == SDLK_ESCAPE) {
			running = false;
		}
	}
}

void JustRight::update() {
	// 5 Seconds
	if (SDL_GetTicks() - startTime >= 5000) {
		running = false;
	}
}

void JustRight::render() {
	// Black Screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	// Draw Test Rectangle (Red)
	SDL_Rect testRect = {300, 200, 200, 200};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &testRect);

	SDL_RenderPresent(renderer);
}

void JustRight::run() {
	while (running) {
		handleEvents();
		update();
		render();

		// 60 FPS
		SDL_Delay(16);
	}
	std::cout << "Render Test Completeded Successfully" << std::endl;
}

int main(int argc, char*argv[]) {
	JustRight game;
	game.run();
	return 0;
}
