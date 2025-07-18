#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

#include "collision.h"

int checkHit(Entity *attackFrom, Entity *attackTo);
int calculateKnockback(Entity *attackFrom, Entity *attackTo);
void calculateFight(Entity *attackFrom, Entity *attackTo);