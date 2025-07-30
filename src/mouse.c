#include "mouse.h"

Mouse initMouse(void) {
    Mouse mouse;

    loadMouse(&mouse);
    printf("Good Mouse Init\n");

    return mouse;
}

void loadMouse(Mouse *mouse) {
    mouse->x = MAP_MID_X;
    mouse->y = MAP_MID_Y;
    mouse->w = MOUSE_WIDTH;
    mouse->h = MOUSE_HEIGHT;
    mouse->r = MOUSE_RADIUS;
    mouse->state = MOUSE_PASSIVE;
}

void updateMouse(Mouse *mouse, int x, int y){
    // Update Mouse Position
    mouse->x = x;
    mouse->x = y;
}

SDL_Rect drawMouseBounds(Mouse *mouse) {
    SDL_Rect mouseTile = {
		mouse->x,
		mouse->y,
		mouse->w,
		mouse->h
	};

	return mouseTile;
}