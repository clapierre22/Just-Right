#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "defs.h"

Entity initEnemy(void);
void spawnEnemy(Entity *enemy, Map *map);
void loadEnemy(Entity *enemy);
SDL_Rect drawEnemy(Entity *enemy, SDL_Renderer *renderer);
void moveEnemy(Entity *enemy);
void updateEnemy(Entity *enemy, Entity *player);
