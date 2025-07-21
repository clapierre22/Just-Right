#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

#include "player.h"
#include "enemy.h"

Point initPoint(void); // Init point
void loadPoint(Point *point); // Load point data
void changePoint(Point *point, PointType newType, SpawnType newSType); // Change point type
void movePoint(Point *point, int newX, int newY); // Move point coords
// void renderPoint(Point *point, SDL_Renderer *renderer); // Render point
void activatePoint(Point *point, Level *level); // Run point logic