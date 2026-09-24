#include "ingame_interface.h"

Interface* interfaceInit(SDL_Renderer* renderer, Entity* player) {
    if (!player || !renderer) return NULL;
    
    Interface* interface = (Interface*)malloc(sizeof(Interface));
    if (!interface) return NULL;
    
    interface->player = player;
    interface->background = loadImageMenu(renderer, "world1.png");

    interface->move_up = 0;
    interface->move_down = 0;
    interface->move_left = 0;
    interface->move_right = 0;
    
    return interface;
}

void destroyInterface(Interface* interface) {
    if (!interface) return;
    destroyImage(interface->background);
    free(interface);
}