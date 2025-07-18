#include "fighting.h"

int checkHit(Entity *attackFrom, Entity *attackTo) {
    SDL_Rect swingBox = {
        attackFrom->x,
        attackFrom->y,
        attackFrom->w,
        attackFrom->h
    };

    return checkHitCollision(swingBox, attackTo);
}

int calculateKnockback(Entity *attackFrom, Entity *attackTo) {
    return 0;
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
    }
}