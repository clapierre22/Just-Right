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
    point->spawn = NOT_SPAWN;
}

void changePoint(Point *point, PointType newType, SpawnType newSType) {
    // Change point type
    point->type = newType;
    point->spawn = newSType;
}

void movePoint(Point *point, int newX, int newY) {
    // Move point coords
    point->x = newX;
    point->y = newY;
}

// void renderPoint(Point *point, SDL_Renderer *renderer) {
//     // Render point
    
// }

void activatePoint(Point *point, Level *level) {
    // Run point logic
    switch (point->type) {
        case POINT_UNASSIGNED: {
            // Reports that point is unassigned
            break;
        }
        case POINT_SPAWN: {
            // Spawns a new entity of specific type
            switch (point->spawn) {
                case NOT_SPAWN: {
                    // Throw error or otherwise tell user that this is not a spawn
                    break;
                }
                case SPAWN_PLAYER: {
                    // Singleplayer
                    if (level->entityCount < MAX_ENTITIES) {
                        level->entities[PLAYER_ONE] = initPlayer();
                        level->entities[PLAYER_ONE].x = point->x; // TODO: Change to use world2screen
                        level->entities[PLAYER_ONE].y = point->y;
                        level->entities[PLAYER_ONE].id = PLAYER_ONE;

                        printf("Player spawned, ID: %d at (%d, %d)\n",
                        level->entities[PLAYER_ONE].id,
                        (int)level->entities[PLAYER_ONE].x,
                        (int)level->entities[PLAYER_ONE].y);

                        level->entityCount++;
                    } else {
                        printf("Max Entity Count: %d has been Reached", MAX_ENTITIES);
                    }

                    break;
                }
                case SPAWN_ENEMY: {
                    if (level->entityCount < MAX_ENEMIES) {
                        level->entities[level->entityCount] = initEnemy();
                        level->entities[level->entityCount].x = point->x;
                        level->entities[level->entityCount].x = point->x;
                        level->entities[level->entityCount].id = level->entityCount + 1;

                        printf("Enemy spawned, ID: %d at (%d, %d)\n",
                        level->entities[level->entityCount].id,
                        (int)level->entities[level->entityCount].x,
                        (int)level->entities[level->entityCount].y);

                        level->entityCount++;
                    } else {
                        printf("Max Enemy Count: %d has been Reached", MAX_ENEMIES);
                    }

                    break;
                }
            }
            break;
        }
        case POINT_GAME: {
            // Objective
            break;
        }
        case POINT_POINT: {
            // Score
            break;
        }
    }
}