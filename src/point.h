#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

#include "player.h"
#include "enemy.h"

Point initPoint(void); // Init point
void loadPoint(Point *point); // Load point data
void changePointType(Point *point, PointType newType); // Change point type
void changePointSpawn(Point *point,SpawnType newSpawn); // Change point spawn type
void changePointStatus(Point *point, PointStatus newStatus); // Change point status
void changePointInterval(Point *point, int newInterval); // Change pointinterval
void movePoint(Point *point, int newX, int newY); // Move point coords
// void renderPoint(Point *point, SDL_Renderer *renderer); // Render point
void activatePoint(Point *point, Level *level); // Run single point logic instance
void runPoint(Point *point, Level *level); // Toggle constant running (activatePoint) of point logic