#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

Map initMap(void);
// static void loadTiles(void);
static void loadMap(Map* map);
void drawMap(SDL_Renderer* renderer, Map* map);
