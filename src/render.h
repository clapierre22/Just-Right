#include <stdio.h>
#include <SDL2/SDL.h>

#include "camera.h"

//SDL_Renderer renderInit(void);

void renderEntity(SDL_Renderer *renderer, const Camera *camera, const Entity *entity);

void renderTile(SDL_Renderer *renderer, const Camera *camera, const RoomTile *tile);

