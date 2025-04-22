#include <stdio.h>
#include <SDL2/SDL.h>

#include "defs.h"
#include "structs.h"

Camera initCamera(void);
//static void loadCamera(Camera *camera);
int withinCamera(Camera *camera, Entity *entity);
int withinCameraTile(Camera *camera, SDL_Rect *tile);
void moveCamera(Camera *camera, Entity *player);

