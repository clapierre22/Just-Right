#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

#include "collision.h"
#include "camera.h"
#include "math.h"

// TODO: Add Level to each check (after spatial hashmap)
int checkHit(Level *level, Entity *attackFrom, Entity *attackTo);
int checkShot(Level *level, Mouse *mouse, Entity *attackTo);
void calculateKnockback(Entity *attackFrom, Entity *attackTo);
void calculateFight(Level *level, Entity *attackFrom, Entity *attackTo);