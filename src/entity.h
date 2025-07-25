#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

#include "collision.h"

Entity initEntity(void);
void loadEntity(Entity *entity);
void modifyEntity(Entity *entity, EntityType type);
void moveEntity(Entity *entity);
void updateEntity(Entity *entity, Level *level);
void normalizeEntityVelocity(Entity *entity, int speed);
SDL_Rect drawEntityBounds(Entity *entity);