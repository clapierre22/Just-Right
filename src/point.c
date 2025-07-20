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

    return;
}
void loadPoint(Point *point) {
    // load point data
    point->id = 0;
    point->x = MAP_MID_X;
    point->y = MAP_MID_Y;
    point->type = POINT_UNASSIGNED;
}

void changePoint(Point *point, PointType type) {
    // Change point type
}

void movePoint(Point *point, int x, int y) {
    // Move point coords
}

void renderPoint(Point *point, SDL_Renderer *renderer) {
    // Render point
}

void activatePoint(Point *point) {
    // Run point logic
}