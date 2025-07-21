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
                    break;
                }
                case SPAWN_ENEMY: {
                    if (level->enemyCount < MAX_ENEMIES) {
                        level->enemies[level->enemyCount] = initEnemy();
                        level->enemies[level->enemyCount].x = point->x;
                        level->enemies[level->enemyCount].x = point->x;
                        level->enemies[level->enemyCount].id = level->enemyCount + 1;

                        printf("Enemy spawned, ID: %d at (%d, %d)\n",
                        level->enemies[level->enemyCount].id,
                        (int)level->enemies[level->enemyCount].x,
                        (int)level->enemies[level->enemyCount].y);

                        level->enemyCount++;
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