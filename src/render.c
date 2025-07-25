#include "render.h"

//SDL_Renderer renderInit(void) {
	// Call SDL_Renderer Init here
//}

void renderEntity(SDL_Renderer *renderer, const Camera *camera, const Entity *entity) {
	// Render Entity
	if (withinCamera(camera, entity)) {
			// Draw Entity
		int screenX, screenY;
		worldToScreen(camera, entity->x, entity->y, &screenX, &screenY);

		if (entity->attacking) {
			// Draw swing box
			SDL_Rect swingBox = {
				screenX + (entity->w / 2) - (PLAYER_BASE_RANGE / 2), // Range formula, make function in math.c; int rangeCenter(int x, Entity *entity); return coord value;
				screenY + (entity->h / 2) - (PLAYER_BASE_RANGE / 2),
				PLAYER_BASE_RANGE,
				PLAYER_BASE_RANGE
			};

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &swingBox);
		}

		SDL_Rect entityBox = {
			screenX,
			screenY,
			(int)(entity->w * camera->zoom),
			(int)(entity->h * camera->zoom)
		};

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(renderer, &entityBox);
	}
}

void renderTile(SDL_Renderer *renderer, const Camera *camera, const RoomTile *tile) {
	// Render Tiles
	if (withinCameraTile(camera, tile)) {
			// Draw Tile
		int screenX, screenY;
		worldToScreen(camera, tile->tileBounds.x, tile->tileBounds.y, &screenX, &screenY);

		SDL_Rect tileBox = {
			screenX,
			screenY,
			(int)(tile->tileBounds.w * camera->zoom),
			(int)(tile->tileBounds.h * camera->zoom)
		};

		SDL_RenderFillRect(renderer, &tileBox);
		//printf("Tile within camera\n");
		
		// Outline
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
		SDL_RenderDrawRect(renderer, &tileBox);
	}
}
