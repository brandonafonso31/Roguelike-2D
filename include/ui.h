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

extern const char* txt_main_menu[];

void renderMainMenuButtons(MainMenu* menu, SDL_Renderer* renderer);
void renderMainMenuUI(MainMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings);

void renderInGameMenuUI(InGameMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings);
void renderWorldTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt);
void renderInventoryTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt);
void renderShopTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt);
void renderUpgradesTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt);
void renderWipTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt);

void switchSettings(int id, SettingsMenu* menu, SDL_Renderer* renderer, double dt, TTF_Font* font, int width, int height, int content_x, int content_y, int line_spacing, int label_width, int value_x);
void renderSettingsUI(SettingsMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings);
void renderMainSettingsTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt, int x, int y, int spacing, int label_w, int val_x);
void renderGraphicSettingsTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt, int x, int y, int spacing, int label_w, int val_x);
void renderSoundSettingsTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt, int x, int y, int spacing, int label_w, int val_x);
#endif