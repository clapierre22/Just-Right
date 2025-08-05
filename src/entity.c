#include "entity.h"

Entity initEntity(void) {
    Entity entity;

    loadEntity(&entity);
    printf("Good Entity Init");

    return entity;
}

void loadEntity(Entity *entity) {
    entity->id = 0;
    entity->x = PLAYER_BASE_X;
    entity->y = PLAYER_BASE_Y;
    entity->w = PLAYER_WIDTH;
    entity->h = PLAYER_HEIGHT;
    entity->velocityX = ENTITY_STOP;
    entity->velocityY = ENTITY_STOP;
    entity->facing = NORTH;
    entity->inputX = ENTITY_STOP;
    entity->inputY = ENTITY_STOP;
    entity->health = PLAYER_BASE_HEALTH;
    entity->damage = PLAYER_BASE_DAMAGE;
    entity->knockback = PLAYER_BASE_KNOCKBACK;
    entity->attacking = FALSE;
    entity->shooting = FALSE;
    entity->hit = FALSE;
    entity->stunTime = ENTITY_STOP;
    entity->coolTime = PLAYER_SWING_COOL;
    entity->onCooldown = FALSE;
    entity->type = ENTITY_UNASSIGNED;
}

void modifyEntity(Entity *entity, EntityType type) {
    entity->type = type;
    switch (type) {
        case ENTITY_UNASSIGNED: {
            break;
        }
        case ENTITY_PLAYER: {
            entity->health = PLAYER_BASE_HEALTH;
            entity->damage = PLAYER_BASE_DAMAGE;
            entity->knockback = PLAYER_BASE_KNOCKBACK;
            break;
        }
        case ENTITY_ENEMY: {
            entity->health = ENEMY_BASE_HEALTH;
            entity->damage = ENEMY_BASE_DAMAGE;
            entity->knockback = ENEMY_BASE_KNOCKBACK;
            break;
        }
        case ENTITY_ITEM: {
            break;
        }
    }
}

void moveEntity(Entity *entity) {
    entity->x += entity->velocityX;
    entity->y += entity->velocityY;
}

void updateEntity(Entity *entity, Level *level) {
    // Update movement, collisions, tracking
    switch (entity->type) {
        case ENTITY_UNASSIGNED: {
            break;
        }
        case ENTITY_PLAYER: {
            // Check Map Collision
            // moveEntity(entity);
            entity->coolTime--;

            normalizeEntityVelocity(entity, PLAYER_SPEED);
            entity->x += entity->velocityX;
            if (checkMapCollision(entity, &level->map, entity->velocityX > 0 ? EAST : WEST)) {
                entity->x -= entity->velocityX;
                entity->velocityX = ENTITY_STOP;
            }

            entity->y += entity->velocityY;
            if (checkMapCollision(entity, &level->map, entity->velocityY > 0 ? SOUTH : NORTH)) {
                entity->y -= entity->velocityY;
                entity->velocityY = ENTITY_STOP;
            }
            
            break;
        }
        case ENTITY_ENEMY: {
            // Check Map Collision

            normalizeEntityVelocity(entity, ENEMY_SPEED);

            entity->x += entity->velocityX;
            if (checkMapCollision(entity, &level->map, entity->velocityX > 0 ? EAST : WEST)) {
                entity->x -= entity->velocityX;
                entity->velocityX = ENTITY_STOP;
            }

            entity->y += entity->velocityY;
            if (checkMapCollision(entity, &level->map, entity->velocityY > 0 ? SOUTH : NORTH)) {
                entity->y -= entity->velocityY;
                entity->velocityY = ENTITY_STOP;
            }

            if (entity->stunTime > 0) { // Check Knockback Stun
                entity->stunTime--;
                if (entity->stunTime == 0) {
                    entity->hit = FALSE;
                    entity->velocityX = ENTITY_STOP;
                    entity->velocityY = ENTITY_STOP;
                }
            } else { // Noraml Tracking
                int dx = level->entities[PLAYER_ONE].x - entity->x;
                int dy = level->entities[PLAYER_ONE].y - entity->y;
                float len = sqrtf(dx * dx + dy * dy);

                // Aggressive (default)
                if (len > 0) {
                    entity->velocityX = (int)(ENEMY_SPEED * dx / len);
                    entity->velocityY = (int)(ENEMY_SPEED * dy / len);
                } else {
                    entity->velocityX = ENTITY_STOP;
                    entity->velocityY = ENTITY_STOP;
                }

                // Extra logic to ensure no overlapping
                if (checkEntityCollision(entity, &level->entities[PLAYER_ONE])) {
                    entity->velocityX = ENTITY_STOP;
                    entity->velocityY = ENTITY_STOP;
                }
            }

            // moveEntity(entity);

            break;
        }
        case ENTITY_ITEM: {
            break;
        }
    }
}

void normalizeEntityVelocity(Entity *entity, int speed) {
    if (entity->velocityX == ENTITY_STOP && entity->velocityY == ENTITY_STOP) return;

    if (entity->velocityX != ENTITY_STOP && entity->velocityY != ENTITY_STOP) {
        // Diagonal movement: normalize
        float len = sqrtf(entity->velocityX * entity->velocityX + entity->velocityY * entity->velocityY);
        if (len > 0) {
            entity->velocityX = (int)(speed * entity->velocityX / len);
            entity->velocityY = (int)(speed * entity->velocityY / len);
        }
    } else {
        // Only one axis or none: clamp to speed, but do NOT set the other axis to zero
        if (entity->velocityX != 0) {
            entity->velocityX = (entity->velocityX > 0) ? speed : -speed;
        }
        if (entity->velocityY != 0) {
            entity->velocityY = (entity->velocityY > 0) ? speed : -speed;
        }
    }

    // Optional version if performance suffers in future (no floating point)
    // // If no movement, return
    // if (entity->velocityX == 0 && entity->velocityY == 0) return;
    
    // // Check if movement is diagonal
    // if (entity->velocityX != 0 && entity->velocityY != 0) {
    //     // Approximate 1/sqrt(2) as 0.7071 * speed
    //     int diagonalSpeed = (speed * 7071) / 10000;  // Fixed-point approximation
    //     entity->velocityX = (entity->velocityX > 0) ? diagonalSpeed : -diagonalSpeed;
    //     entity->velocityY = (entity->velocityY > 0) ? diagonalSpeed : -diagonalSpeed;
    // } else {
    //     // Straight movement
    //     if (entity->velocityX != 0) {
    //         entity->velocityX = (entity->velocityX > 0) ? speed : -speed;
    //     }
    //     if (entity->velocityY != 0) {
    //         entity->velocityY = (entity->velocityY > 0) ? speed : -speed;
    //     }
    // }
}

SDL_Rect drawEntityBounds(Entity *entity) {
    SDL_Rect entityTile = {
		entity->x,
		entity->y,
		entity->w,
		entity->h
	};

	return entityTile;
}