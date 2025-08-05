#include "fighting.h"

int checkHit(Level *level, Entity *attackFrom, Entity *attackTo) {
    SDL_Rect swingBox = {
        attackFrom->x - (attackFrom->w / 2) - (PLAYER_BASE_RANGE / 2), // Switch PBR for attackFrom->range
        attackFrom->y - (attackFrom->h / 2) - (PLAYER_BASE_RANGE / 2),
        PLAYER_BASE_RANGE,
        PLAYER_BASE_RANGE
    };

    return checkHitCollision(level, swingBox, attackTo);
}

int checkShot(Level *level, Mouse *mouse, Entity *attackTo) {
    // int screenX, screenY;
    // worldToScreen(&level->camera, mouse->x, mouse->y, &screenX, &screenY);
    SDL_Rect shotBox = {
        // mouse->x - (mouse->w / 2),
        // mouse->y - (mouse->h / 2),
        // screenX - (mouse->w / 2),
        // screenY - (mouse->h / 2),
		// (int)(mouse->w * level->camera.zoom),
		// (int)(mouse->h * level->camera.zoom)
        mouse->x,
        mouse->y,
        mouse->w,
        mouse->h
    };

    worldToScreenRect(&level->camera, &shotBox);

    printf("ShotBox: x=%d y=%d w=%d h=%d\n", shotBox.x, shotBox.y, shotBox.w, shotBox.h);
    printf("Target: x=%d y=%d w=%d h=%d\n", attackTo->x, attackTo->y, attackTo->w, attackTo->h);

    printf("Hit: %d\n", checkHitCollision(level, shotBox, attackTo));

    return checkHitCollision(level, shotBox, attackTo);
}

void calculateKnockback(Entity *attackFrom, Entity *attackTo) {
    // TODO: Does not throw error, but does not knock back entity
    // Moves the attacked back the number of units equal to the attackers knockback
    // Calculate direction
    int dx = attackTo->x - attackFrom->x;
    int dy = attackTo->y - attackFrom->y;

    // Normalize direction
    float len = sqrtf(dx * dx + dy * dy);
    if (len == 0) len = 1; // Prevent division by zero

    // Apply knockback
    attackTo->velocityX = (int)(attackFrom->knockback * dx / len);
    attackTo->velocityY = (int)(attackFrom->knockback * dy / len);

    // Set hit tag to TRUE, stun to 10 frames
    attackTo->hit = TRUE;
    attackTo->stunTime = BASE_STUN;
}

void calculateFight(Level *level, Entity *attackFrom, Entity *attackTo) {
    // P: Entity attacking, Entity being attacked
    // VOID, Alters attacked health based on attacking damage value if hit 
    if (attackFrom->attacking) {
        printf("Hit Detected\n");
        if (checkHit(level, attackFrom, attackTo)) {
            printf("Hit Hit\n");

            // Future space for weapons adding to damage
            printf("Attack Target Health Before: %d\n", attackTo->health);
            attackTo->health -= attackFrom->damage;
            printf("Delt %d Damage, New Target Health: %d\n", attackFrom->damage, attackTo->health);

            // Calculate knockback here
            calculateKnockback(attackFrom, attackTo);
            printf("Attack Target Knockback Applied: %d\n", attackFrom->knockback);
        }
    }

    if (attackFrom->shooting) {
        printf("Shot Detected\n");
        if (checkShot(level, &level->mouse, attackTo)) {
            printf("Shot Hit\n");
            // Future space for weapons adding to damage
            printf("Attack Target Health Before: %d\n", attackTo->health);
            attackTo->health -= attackFrom->damage;
            printf("Delt %d Damage, New Target Health: %d\n", attackFrom->damage, attackTo->health);

            // Calculate knockback here
            calculateKnockback(attackFrom, attackTo);
            printf("Attack Target Knockback Applied: %d\n", attackFrom->knockback);
        }
        attackFrom->shooting = FALSE;
    }
}