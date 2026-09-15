#ifndef POLLEVENTS_H
#define POLLEVENTS_H

#include <SDL2/SDL.h>
#include "menu.h"
#include "game_state.h"

int pollEventsMenu(MainMenu* menu,SDL_Event* event, GameState* state);
int pollEventsInGameMenu(InGameMenu* menu, SDL_Event* event, GameState* state);
int pollEventsSettingsMenu(SettingsMenu* menu, SDL_Event* event, GameState* state);

#endif