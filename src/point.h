#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

Point initPoint(void); // Init point
void loadPoint(Point *point); // Load point data
void changePoint(Point *point, PointType type); // Change point type
void movePoint(Point *point, int x, int y); // Move point coords
void renderPoint(Point *point, SDL_Renderer *renderer); // Render point
void activatePoint(Point *point); // Run point logic