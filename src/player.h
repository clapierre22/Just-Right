#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>

#include "structs.h"
#include "defs.h"

#include "collision.h"
#include "map.h"

Entity initPlayer(void);
void loadPlayer(Entity *player);
SDL_Rect drawPlayer(Entity *player);
// void render(SDL_Renderer *renderer, Entity *entity);
void movePlayer(Entity *player);
void updatePlayer(Entity *player, Map *map);
