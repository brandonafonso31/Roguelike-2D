#ifndef MENU_INGAME_H
#define MENU_INGAME_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include "settings.h"
#include "image_loader.h"
#include "button.h"
#include "drawing_function.h"
#include "menu.h"
#include "fps_utils.h"


void ingameMenu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings);
int pollEventsInGameMenu(InGameMenu* menu, SDL_Event* event, int* state);

#endif