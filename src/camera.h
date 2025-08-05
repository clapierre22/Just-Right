#include <stdio.h>
#include <SDL2/SDL.h>

#include "defs.h"
#include "structs.h"

Camera initCamera(void);
//static void loadCamera(Camera *camera);
int withinCamera(const Camera *camera, const Entity *entity);
int withinCameraTile(const Camera *camera, const RoomTile *tile);
int withinCameraPoint(const Camera *camera, const Point *point);
int withinCameraMouse(const Camera *camera, const Mouse *mouse);
void moveCamera(Camera *camera, const Entity *player);
void reportCamera(const Camera *camera, float *x, float *y, float *w, float *h);

