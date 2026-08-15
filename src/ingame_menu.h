#ifndef MENU_INGAME_H
#define MENU_INGAME_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include "settings.h"
#include "image_loader.h"
#include "button.h"
#include "drawing_function.h"

typedef struct {
    Image* background;
    Image* Dungeon;
    Image* play;
    Image* pp;
    Image* donjon;
    Image* quest;
    Image* shop;

    int selected_index;
    int button_count;
} InGameMenu;

void ingameMenu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings);

#endif