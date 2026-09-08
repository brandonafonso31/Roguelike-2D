#ifndef Entity_H
#define Entity_H

#include "statistics.h"

typedef struct {
    Statistics* stats;
} Entity;

Entity* initEntity(Statistics* stats);

#endif