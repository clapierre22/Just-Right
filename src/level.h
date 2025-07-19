#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

#include "map.h"
#include "render.h"

void initLevel(void); // initLevel generates the player, enemies, map; holds within the level object
void changeMap(Map *map); // changes map (default map is current demo square)
void updateLevel(Level *level); // runs the update function on all Entities, points
void renderLevel(SDL_Renderer *renderer, Camera *camera, Level *level); // renders the level, entities, points
