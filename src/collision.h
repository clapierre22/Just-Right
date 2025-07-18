#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

int collision(SDL_Rect a, SDL_Rect b);
int checkMapCollision(Entity *entity, Map *map, int direction);
int checkEntityCollision(Entity *a, Entity *b);
int checkHitCollision(SDL_Rect swingBox, Entity *attackTo);
void collisionDebug(SDL_Renderer *renderer, SDL_Rect a, SDL_Rect b);
