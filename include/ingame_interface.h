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
    int move_up;
    int move_down;
    int move_left;
    int move_right;
} Interface;

Interface* interfaceInit(SDL_Renderer* renderer, Entity* player); //need to add csv with dungeon information (entity, background path ...)
void destroyInterface(Interface* interface);

#endif