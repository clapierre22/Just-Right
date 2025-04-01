#ifndef JUSTRIGHT_H
#define JUSTRIGHT_H

#include <SDL2/SDL.h>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;
const int FLOORY = 470;

class JustRight { 
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		bool running;
		std::vector<SDL_Rect> platforms;
		Uint32 startTime;
	public:
		JustRight();
		~JustRight();
		void run();
		void handleEvents();
		void update();
		void render();
};

#endif
