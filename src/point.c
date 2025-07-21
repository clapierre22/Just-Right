#include "point.h"

// Points are logic blocks on the level that can serve multiple functions
    // spawnPoint; where the spawn logic operates
    // objectivePoint; gameplay/progession logic
    // pointPoint; score logic

Point initPoint(void){
    // Init point
    Point point;

    loadPoint(&point);
    printf("Good Point Init\n");

    return point;
}
void loadPoint(Point *point) {
    // load point data
    point->id = 0;
    point->x = MAP_MID_X;
    point->y = MAP_MID_Y;
    point->w = TILE_SIZE;
    point->h = TILE_SIZE;
    point->type = POINT_UNASSIGNED;
}

void changePoint(Point *point, PointType newType) {
    // Change point type
    point->type = newType;
}

void movePoint(Point *point, int newX, int newY) {
    // Move point coords
    point->x = newX;
    point->y = newY;
}

// void renderPoint(Point *point, SDL_Renderer *renderer) {
//     // Render point
    
// }

void activatePoint(Point *point) {
    // Run point logic
    switch (point->type) {
        case POINT_UNASSIGNED: {
            
            break;
        }
        case POINT_SPAWN: {
            
            break;
        }
        case POINT_GAME: {
            
            break;
        }
        case POINT_POINT: {
            
            break;
        }
    }
}