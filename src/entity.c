#include "entity.h"

Entity* initEntity(const char* name, Statistics* stats, int x, int y){
    Entity* entity = (Entity*)malloc(sizeof(Entity));

    if (!name){
        strcpy(entity->name, "Unknown");
    } else {
        strncpy(entity->name, name, sizeof(entity->name) - 1);
        entity->name[sizeof(entity->name) - 1] = '\0';
    }

    if (!stats){
        stats = setBasicStats();
    } else entity->stats = stats;

    entity->pos_x = x; entity->pos_y = y;
    entity->is_alive = 1;

    return entity;
}

void destroyEntity(Entity* entity) {
    if (!entity) return;

    if (entity->stats) {
        destroyStatistics(entity->stats);
    }
    
    free(entity);
}

void updateHP(Entity* entity, double damage) {
    if (!entity || !entity->stats) return;
    
    int* hp = &entity->stats->hp;
    int max_hp = entity->stats->max_hp;
    
    *hp = *hp - (int)damage;
    
    if (*hp > max_hp) *hp = max_hp;
    else if (*hp < 0) *hp = 0;
}