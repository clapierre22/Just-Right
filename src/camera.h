#include <stdio.h>
#include <SDL2/SDL.h>

#include "defs.h"
#include "structs.h"

Camera initCamera(void);
//static void loadCamera(Camera *camera);
int withinCamera(const Camera *camera, const Entity *entity);
int withinCameraTile(const Camera *camera, const RoomTile *tile);
void moveCamera(Camera *camera, const Entity *player);
void worldToScreen(const Camera *camera, float worldX, float worldY, int *screenX, int *screenY);

