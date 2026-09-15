#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "settings.h"
#include "fps_utils.h"
#include "drawing_function.h"
#include "fps_utils.h"
#include "image.h"
#include "menu.h"
#include "button.h"
#include "json_loader.h"

extern const char* txt_main_menu[];

void renderMainMenuUI(MainMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings);
void renderInGameMenuUI(InGameMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings, EntityDatabase* db_entities);
void renderSettingsUI(SettingsMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings);

#endif