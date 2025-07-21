#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

Point initPoint(void); // Init point
void loadPoint(Point *point); // Load point data
void changePoint(Point *point, PointType newType); // Change point type
void movePoint(Point *point, int newX, int newY); // Move point coords
// void renderPoint(Point *point, SDL_Renderer *renderer); // Render point
void activatePoint(Point *point); // Run point logic