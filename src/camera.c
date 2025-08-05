#include "camera.h"

static void loadCamera(Camera *camera) {
	// TODO: assign x, y, w, h
	camera->x = CAMERA_START_X;
	camera->y = CAMERA_START_Y;
	camera->w = CAMERA_WIDTH;
	camera->h = CAMERA_HEIGHT;
	camera->zoom = CAMERA_ZOOM;
}

Camera initCamera(void) {
	Camera camera;
	
	loadCamera(&camera);
	printf("Good Camera Load\n");

	return camera;
}

int withinCamera(const Camera *camera, const Entity *entity) {
	// TODO: Returns TRUE if 
	// 	entity.x within camera.w and camera.x
	// 	and
	// 	entity.y within camera.h and camera.y
	// 	else Returns FALSE
		
	// Calculate effective width, height of Camera
	float eW = camera->w / camera->zoom;
	float eH = camera->h / camera->zoom;

	// Calculate Camera bounds
	float cL = camera->x - eW / 2;
	float cR = camera->x + eW / 2;
	float cT = camera->y - eH / 2;
	float cB = camera->y + eH / 2;

	// Calculate Entity bounds
	float eL = entity->x;
	float eR = entity->x + entity->w;
	float eT = entity->y;
	float eB = entity->y + entity->h;

	return !(eR < cL
		|| eL > cR
		|| eB < cT
		|| eT > cB);
}

int withinCameraTile(const Camera *camera, const RoomTile *tile) {
	// TODO: Create a seperate func to use with tiles
	
	// Calculate effective width, height of Camera
	float eW = camera->w / camera->zoom;
	float eH = camera->h / camera->zoom;

	// Calculate Camera bounds
	float cL = camera->x - eW / 2;
	float cR = camera->x + eW / 2;
	float cT = camera->y - eH / 2;
	float cB = camera->y + eH / 2;

	// Calculate Tile bounds
	float tL = tile->tileBounds.x;
	float tR = tile->tileBounds.x + tile->tileBounds.w;
	float tT = tile->tileBounds.y;
	float tB = tile->tileBounds.y + tile->tileBounds.h;

	return !(tR < cL
		|| tL > cR
		|| tB < cT
		|| tT > cB);
}

int withinCameraPoint(const Camera *camera, const Point *point) {
	// TODO: Create a seperate func to use with tiles
	
	// Calculate effective width, height of Camera
	float eW = camera->w / camera->zoom;
	float eH = camera->h / camera->zoom;

	// Calculate Camera bounds
	float cL = camera->x - eW / 2;
	float cR = camera->x + eW / 2;
	float cT = camera->y - eH / 2;
	float cB = camera->y + eH / 2;

	// Calculate Tile bounds
	float pL = point->x;
	float pR = point->x + point->w;
	float pT = point->y;
	float pB = point->y + point->h;

	return !(pR < cL
		|| pL > cR
		|| pB < cT
		|| pT > cB);
}

int withinCameraMouse(const Camera *camera, const Mouse *mouse) {
	return 1;
}

void moveCamera(Camera *camera, const Entity *player) {
	// TODO: moves the camera x,y when
	// 	player is moved (call after updating player x,y
	// These two find the mid point of the player, could add to player.c
	//
	// TODO: SAME HERE, USER POINTERS AS WELL
	camera->x = (player->x + (player->w / 2));
	camera->y = (player->y + (player->h / 2));

	// PROBLEM: Camera is spawning off of player, too far top right

	// Keep Camera in Bounds
	//if (camera->x < 0) { camera->x = 0; }
	//if (camera->y < 0) { camera->y = 0; }

	//if (camera->x > SCREEN_WIDTH - camera->w) { 
	//	camera->x = SCREEN_WIDTH - camera->w; 
	//}
	//if (camera->y > SCREEN_HEIGHT - camera->h) {
	//	camera->y = SCREEN_WIDTH - camera->h;
	//}	
}

void reportCamera(const Camera *camera, float *x, float *y, float *w, float *h) {
	// Reports the current state of the camera, used in math and render
	// float cW = camera->w / camera->zoom;
	// float cH = camera->h / camera->zoom;

	// float cX = camera->x - cW / 2;
	// float cY = camera->y - cH / 2;
	
	*w = camera->w / camera->zoom;
	*h = camera->h / camera->zoom;

	*x = camera->x - (*w / 2); // These could be wrong, want to use int in memory
	*y = camera->y - (*h / 2);
}