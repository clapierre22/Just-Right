#include "math.h"

void worldToScreen(const Camera *camera, float worldX, float worldY, int *screenX, int *screenY) {
	// Conversion from given world x, y to camera zoom adjusted screen x, y

    float cW, cH, cX, cY; // TODO: Find a way for every function to use same memory, it won't be called twice at the same time
    reportCamera(camera, &cX, &cY, &cW, &cH);

	*screenX = (int)((worldX - cX) * camera->zoom);
	*screenY = (int)((worldY - cY) * camera->zoom);	
}

void screenToWorld(const Camera *camera, int screenX, int screenY, float *worldX, float *worldY) {
	// TODO
    // Conversion from screen x,y to camera zoom adjusted world x,y
    float cW, cH, cX, cY;
    reportCamera(camera, &cX, &cY, &cW, &cH);

    *worldX = (int)(screenX / camera->zoom) + cX;
    *worldY = (int)(screenY / camera->zoom) + cY;
}

void worldToScreenSize(const Camera *camera, float worldW, float worldH, int *screenW, int *screenH) {
    *screenW = (int)(worldW * camera->zoom);
    *screenH = (int)(worldH * camera->zoom);
}

void screenToWorldSize(const Camera *camera, int screenW, int screenH, float *worldW, float *worldH) {
    *worldW = (int)(screenW / camera->zoom);
    *worldH = (int)(screenH / camera->zoom);
}

void worldToScreenRect(const Camera *camera, SDL_Rect *rect) {
	// TODO
    // Conversion from given world SDL rect to camera zoom adjusted screen SDL rect
    // Take in rect that is copy of target rect, then changes to be used in tandem
    float cW, cH, cX, cY;
    reportCamera(camera, &cX, &cY, &cW, &cH);

    int screenX, screenY;
    worldToScreen(camera, rect->x, rect->y, &screenX, &screenY);

    int screenW, screenH;
    worldToScreenSize(camera, rect->w, rect->h, &screenW, &screenH);

    rect->x = screenX;
    rect->y = screenY;
    rect->w = screenW;
    rect->h = screenH;
}

void screenToWorldRect(const Camera *camera, SDL_Rect *rect) {
	// TODO
    // Conversion from screen SDL rect to camera zoom adjusted world SDL rect
    float cW, cH, cX, cY;
    reportCamera(camera, &cX, &cY, &cW, &cH);

    int worldX, worldY;
    worldToScreen(camera, rect->x, rect->y, &worldX, &worldY);

    int worldW, worldH;
    worldToScreenSize(camera, rect->w, rect->h, &worldW, &worldH);

    rect->x = worldX;
    rect->y = worldY;
    rect->w = worldW;
    rect->h = worldH;
}

void worldToScreenMouse(const Camera *camera, Mouse *mouse) {
	// TODO
    // Conversion from given world mouse to camera zoom adjusted screen mouse, used for click detection
    float cW, cH, cX, cY;
    reportCamera(camera, &cX, &cY, &cW, &cH);
}

void screenToWorldMouse(const Camera *camera, Mouse *mouse) {
	// TODO
    // Conversion from screen mouse to camera zoom adjusted world mouse, used for click detection
    float cW, cH, cX, cY;
    reportCamera(camera, &cX, &cY, &cW, &cH);
}