#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>

#include "structs.h"
#include "defs.h"

Entity initPlayer(void);
void loadPlayer(Entity *player);
SDL_Rect drawPlayer(Entity *player);
