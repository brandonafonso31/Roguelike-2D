#ifndef JSON_LOADER_H
#define JSON_LOADER_H

#include "entity.h"
#include "cJSON.h"
#include "paths.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    Entity* player;
    Entity** entities;
    int entity_count;
} EntityDatabase;

EntityDatabase* loadEntitiesFromJson(const char* filepath);
void destroyEntityDatabase(EntityDatabase* db);

#endif