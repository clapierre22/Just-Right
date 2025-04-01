#include <iostream>
#include <SDL2/SDL.h>

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BOX_SIZE = 50;

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL initialization failed: " 
	<< SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Window Test", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, 
        SCREEN_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window creation failed: " 
	<< SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 
		    -1, 
		    SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cerr << "Renderer creation failed: " 
		<< SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    std::cout << "SDL2 Window Test - Successfully initialized!" 
	    << std::endl;
    std::cout << "Press ESC to quit or click the close button" 
	    << std::endl;

    // Main loop variables
    bool running = true;
    SDL_Event event;
    int boxX = (SCREEN_WIDTH - BOX_SIZE) / 2;
    int boxY = (SCREEN_HEIGHT - BOX_SIZE) / 2;
    int boxVelX = 2, boxVelY = 2;

    // Main loop
    while (running) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }

        // Update box position (simple animation)
        boxX += boxVelX;
        boxY += boxVelY;
        
        // Bounce off walls
        if (boxX <= 0 || boxX >= SCREEN_WIDTH - BOX_SIZE) 
		boxVelX = -boxVelX;
        if (boxY <= 0 || boxY >= SCREEN_HEIGHT - BOX_SIZE) 
		boxVelY = -boxVelY;

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        // Draw box
        SDL_Rect box = { boxX, boxY, BOX_SIZE, BOX_SIZE };
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
        SDL_RenderFillRect(renderer, &box);

        // Update screen
        SDL_RenderPresent(renderer);

        // Cap frame rate
        SDL_Delay(16); // ~60 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Test completed successfully!" << std::endl;
    return 0;
}
