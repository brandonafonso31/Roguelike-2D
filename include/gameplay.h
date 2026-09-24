#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include "settings.h"
#include "fps_utils.h"
#include "paths.h"
#include "poll_events.h"
#include "ui.h"
#include "game_state.h"
#include "json_loader.h"
#include "ingame_interface.h"

GameState gameplay(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings, Entity* player, EntityDatabase* db_entities);

#endif