#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "settings.h"
#include "fps_utils.h"
#include "drawing_function.h"
#include "fps_utils.h"
#include "image_loader.h"
#include "menu.h"

extern const char* txt_main_menu[];

void renderMainMenuUI(MainMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings);
void renderUI(FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings);
void renderInGameMenuUI(InGameMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings);

void renderWorldTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt);
void renderInventoryTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt);
void renderShopTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt);
void renderUpgradesTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt);
void renderWipTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt);

#endif