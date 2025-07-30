#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

Mouse initMouse(void); // Initialize Mouse Object
void loadMouse(Mouse *mouse); // Load Mouse Object
void updateMouse(Mouse *mouse, int x, int y); // Update Mouse Position
SDL_Rect drawMouseBounds(Mouse *mouse); // Draw Mouse Bounds
