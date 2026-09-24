#include "ingame_interface.h"

Interface* interfaceInit(SDL_Renderer* renderer, Entity* player) {
    if (!player || !renderer) return NULL;
    
    Interface* interface = (Interface*)malloc(sizeof(Interface));
    if (!interface) return NULL;
    
    interface->player = player;
    interface->background = loadImageMenu(renderer, "world1.png");
    return interface;
}

void destroyInterface(Interface* interface) {
    if (!interface) return;
    destroyImage(interface->background);
    free(interface);
}