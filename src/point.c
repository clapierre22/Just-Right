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
    point->status = POINT_STOP;
    point->interval = POINT_BASE_INTERVAL;

    SDL_Rect box = {
        point->x,
        point->y,
        TILE_SIZE,
        TILE_SIZE
    };
    point->hitBox = box;
}

void changePointType(Point *point, PointType newType) {
    // Change point type
    point->type = newType;
}

void changePointSpawn(Point *point,SpawnType newSpawn) {
    // Change point spawn type
    point->spawn = newSpawn;
}

void changePointStatus(Point *point, PointStatus newStatus) {
    // Change point status
    point->status = newStatus;
}

void changePointInterval(Point *point, int newInterval) {
    // Change pointinterval
    point->interval = newInterval;
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
                    // if (level->entityCount = MAX_ENTITIES) {
                    //     point->status = POINT_PAUSE;
                    //     printf("Max Entity Count: %d has been Reached", MAX_ENTITIES);
                    //     break;
                    // }
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

                        point->status = POINT_PAUSE;
                        point->interval = POINT_BASE_INTERVAL;

                    } else {
                        printf("Max Entity Count: %d has been Reached", MAX_ENTITIES);
                    }

                    break;
                }
                case SPAWN_ENEMY: {
                    if (checkPointCollision(&level->camera, point, &level->entities[PLAYER_ONE])) {
                        // If player is on spawn point, do not spawn enemy
                        // TODO: This works, but needs to be run through world2screen
                        // TODO: Convert collisions to use w2s function
                        point->status = POINT_PAUSE;
                        break;
                    }

                    if (level->entityCount < MAX_ENEMIES) {
                        level->entities[level->entityCount] = initEnemy();
                        level->entities[level->entityCount].x = point->x;
                        level->entities[level->entityCount].y = point->y;
                        level->entities[level->entityCount].id = level->entityCount + 1;

                        printf("Enemy spawned, ID: %d at (%d, %d)\n",
                        level->entities[level->entityCount].id,
                        (int)level->entities[level->entityCount].x,
                        (int)level->entities[level->entityCount].y);

                        level->entityCount++;

                        point->status = POINT_PAUSE;
                        point->interval = POINT_BASE_INTERVAL;

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

void runPoint(Point *point, Level *level) { 
    // Toggle constant running (activatePoint) of point logic
    switch (point->status) {
        case POINT_STOP: {
            // Break out of loop
            break;
        }
        case POINT_RUN: {
            activatePoint(point, level);
            break;
        }
        case POINT_PAUSE: {
            // Unique logic for certain points, including holding spawning of entities
            switch (point->spawn) {
                case SPAWN_PLAYER: {
                    // Wait for player to die, then POINT_RUN
                    break;
                }
                case SPAWN_ENEMY: {
                    point->interval--;
                    // printf("Point is on pause");
                    if (point->interval <= 0) point->status = POINT_RUN;
                    break;
                }
            }
            break;
        }
        case POINT_ERROR: {
            // Report Error, Remove Point
            break;
        }
    }
}