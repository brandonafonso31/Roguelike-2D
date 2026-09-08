#include "entity.h"

Entity* initEntity(const char* name, Statistics* stats){
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


    return entity;
}