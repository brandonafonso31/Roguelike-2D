#ifndef POLLEVENTS_H
#define POLLEVENTS_H

#include <SDL2/SDL.h>
#include "menu.h"

int pollEvents(MainMenu* menu,SDL_Event* event, int* state);

#endif