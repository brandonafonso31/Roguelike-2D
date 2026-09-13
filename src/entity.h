#ifndef Entity_H
#define Entity_H

#include <stdlib.h>
#include <string.h>
#include "statistics.h"

#define MAX_NAME_LENGTH 32

typedef struct {
    char name[MAX_NAME_LENGTH];
    Statistics* stats;
    int pos_x, pos_y;
    int is_alive;
} Entity;

Entity* initEntity(const char* name, Statistics* stats, int x, int y);
void destroyEntity(Entity* entity);
void updateHP(Entity* entity, double damage);

#endif