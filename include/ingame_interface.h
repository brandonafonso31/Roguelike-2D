#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include "settings.h"
#include "image.h"
#include "entity.h"

typedef struct {
    Entity* player;
    Image* background;
    // Camera ?
    // hp bar
    // mini map ?

} Interface;

Interface* interfaceInit(SDL_Renderer* renderer, Entity* player); //need to add csv with dungeon information (entity, background path ...)
void destroyInterface(Interface* interface);

#endif