#ifndef SETTINGS_MENU_H
#define SETTINGS_MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "settings.h"
#include "fps_utils.h"
#include "paths.h"
#include "poll_events.h"
#include "ui.h"

GameState settingsMenu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings);

#endif