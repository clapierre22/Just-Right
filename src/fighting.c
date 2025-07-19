#include "fighting.h"

int checkHit(Entity *attackFrom, Entity *attackTo) {
    SDL_Rect swingBox = {
        attackFrom->x - + (attackFrom->w / 2) - (PLAYER_BASE_RANGE / 2), // Switch PBR for attackFrom->range
        attackFrom->y - + (attackFrom->w / 2) - (PLAYER_BASE_RANGE / 2),
        PLAYER_BASE_RANGE,
        PLAYER_BASE_RANGE
    };

    return checkHitCollision(swingBox, attackTo);
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

void calculateFight(Entity *attackFrom, Entity *attackTo) {
    // P: Entity attacking, Entity being attacked
    // VOID, Alters attacked health based on attacking damage value if hit 
    if (checkHit(attackFrom, attackTo)) {
        printf("Hit Detected\n");
        // Future space for weapons adding to damage
        printf("Attack Target Health Before: %d\n", attackTo->health);
        attackTo->health -= attackFrom->damage;
        printf("Delt %d Damage, New Target Health: %d\n", attackFrom->damage, attackTo->health);

        // Calculate knockback here
        calculateKnockback(attackFrom, attackTo);
        printf("Attack Target Knockback Applied: %d\n", attackFrom->knockback);
    }
}