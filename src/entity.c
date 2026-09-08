#include "entity.h"

Entity* initEntity(Statistics* stats){
    Entity* entity;
    if (!stats){
        stats = setBasicStats();
    }

    entity->stats = stats;
    return entity;
}