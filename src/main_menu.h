#ifndef MAINMENU_H
#define MAINMENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "settings.h"
#include "fps_utils.h"
#include "paths.h"
#include "poll_events.h"
#include "ui.h"
#include "menu.h"

void mainMenu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings);
    
#endif