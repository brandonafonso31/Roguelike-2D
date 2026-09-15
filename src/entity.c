#include "entity.h"

Entity* initEntity(const char* name, Statistics* stats) {
    Entity* entity = (Entity*)malloc(sizeof(Entity));

    if (!name){
        strcpy(entity->name, "Unknown");
    } else {
        strncpy(entity->name, name, sizeof(entity->name) - 1);
        entity->name[sizeof(entity->name) - 1] = '\0';
    }

    if (!stats){
        stats = InitBasicStats();
    } else entity->stats = stats;

    entity->pos_x = 0; entity->pos_y = 0;
    entity->is_alive = 1;
    entity->hp = stats->max_hp;
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
    
    int* hp = &entity->hp;
    int max_hp = entity->stats->max_hp;
    
    *hp = *hp - (int)damage;
    
    if (*hp > max_hp) *hp = max_hp;
    else if (*hp < 0) *hp = 0;
}