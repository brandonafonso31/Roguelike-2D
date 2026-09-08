#ifndef Entity_H
#define Entity_H

#include <stdlib.h>
#include <string.h>
#include "statistics.h"

#define MAX_NAME_LENGTH 32

typedef struct {
    char name[MAX_NAME_LENGTH];
    Statistics* stats;
} Entity;

Entity* initEntity(const char* name, Statistics* stats);
void destroyEntity(Entity* entity);

#endif