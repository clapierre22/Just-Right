#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

#include "map.h"
#include "render.h"
#include "player.h"
#include "enemy.h"
#include "fighting.h"
#include "camera.h"
#include "point.h"
#include "entity.h"
#include "mouse.h"

Level initLevel(void); // initLevel generates the player, enemies, map; holds within the level object
void loadLevel(Level *level); // loads level information
void spawnEntities(Level *level); // placeholder for spawn and spawnpoint logic
void changeMap(Level *level, Map *map); // changes map (default map is current demo square)
void updateLevel(Level *level); // runs the update function on all Entities, points
void renderLevel(Level *level, SDL_Renderer *renderer); // renders the level, entities, points
void destroyLevel(Level *level); // free level-specific memory
