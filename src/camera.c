#include "camera.h"

static void loadCamera(Camera *camera) {
	// TODO: assign x, y, w, h
	camera->x = CAMERA_START_X;
	camera->y = CAMERA_START_Y;
	camera->w = CAMERA_WIDTH;
	camera->h = CAMERA_HEIGHT;
}

Camera initCamera(void) {
	Camera camera;
	
	loadCamera(&camera);
	printf("Good Camera Load\n");

	return camera;
}

int withinCamera(Camera *camera, Entity *entity) {
	// TODO: Returns TRUE if 
	// 	entity.x within camera.w and camera.x
	// 	and
	// 	entity.y within camera.h and camera.y
	// 	else Returns FALSE

	// Check all boundaries
	// TODO CHANGE TO POINTERS
	int boundX = (camera->x - entity->x) 
		| ((entity->x + entity->w) - (camera->x + camera->w));

	int boundY = (camera->y - entity->y)
		| ((entity->y + entity->h) - (camera->y + camera->h));
		
	// Returns 0 if boundX or boundY is negative (entity not within camera)
	return !((boundX | boundY) >> (sizeof(int) * 8 - 1));
}

int withinCameraTile(Camera *camera, SDL_Rect *tile) {
	// TODO: Create a seperate func to use with tiles
	int boundX = (camera->x - tile->x) | ((tile->x + tile->w) - (camera->x + camera->w));

	int boundY = (camera->y - tile->y) | ((tile->y + tile->h) - (camera->y + camera->h));

	return !((boundX | boundY) >> (sizeof(int) * 8 - 1));
}

void moveCamera(Camera *camera, Entity *player) {
	// TODO: moves the camera x,y when
	// 	player is moved (call after updating player x,y
	// These two find the mid point of the player, could add to player.c
	//
	// TODO: SAME HERE, USER POINTERS AS WELL
	camera->x = (player->x + (player->w / 2)) - (CAMERA_WIDTH / 2);
	camera->y = (player->y + (player->h / 2)) - (CAMERA_HEIGHT / 2);

	// Keep Camera in Bounds
	if (camera->x < 0) { camera->x = 0; }
	if (camera->y < 0) { camera->y = 0; }

	if (camera->x > SCREEN_WIDTH - camera->w) { 
		camera->x = SCREEN_WIDTH - camera->w; 
	}
	if (camera->y > SCREEN_HEIGHT - camera->h) {
		camera->y = SCREEN_WIDTH - camera->h;
	}	
}
