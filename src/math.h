#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

#include "camera.h"
#include "mouse.h"

void worldToScreen(const Camera *camera, float worldX, float worldY, int *screenX, int *screenY);
void screenToWorld(const Camera *camera, int screenX, int screenY, float *worldX, float *worldY);
void worldToScreenSize(const Camera *camera, float worldW, float worldH, int *screenW, int *screenH);
void screenToWorldSize(const Camera *camera, int screenW, int screenH, float *worldW, float *worldH);
void worldToScreenRect(const Camera *camera, SDL_Rect *rect);
void screenToWorldRect(const Camera *camera, SDL_Rect *rect);
void worldToScreenMouse(const Camera *camera, Mouse *mouse);
void screenToWorldMouse(const Camera *camera, Mouse *mouse);