#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "camera.h"
#include "render.h"

#define RAND_TOP 5

Map initMap(void);
// static void loadTiles(void);
// static void loadMap(Map *map);
void drawMap(SDL_Renderer *renderer, Camera *camera, Map *map);
