#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include "settings.h"
#include "image_loader.h"
#include "button.h"

#define MAX_BUTTONS 4

typedef enum {
    MENU_NEW_GAME,
    MENU_LOAD_GAME,
    MENU_SETTINGS,
    MENU_QUIT
} MainMenuAction;

typedef struct {
    Image* background;
    Image* cursor;
    /*Image* title;
    Image* play_button;
    Image* settings_button;
    Image* quit_button;
    Image* play_button_hover;
    Image* settings_button_hover;
    Image* quit_button_hover;*/

    int selected_index;
    int button_count;
} MainMenu;

MainMenu* menuCreate(SDL_Renderer* renderer, GameSettings* settings);
void destroyMenu(MainMenu* menu);
MainMenuAction getSelectedActionMenu(MainMenu* menu);

typedef enum {
    INGAME_PLAY,
    INGAME_BACK,
    INGAME_QUIT,
} InGameMenuAction;

typedef struct {
    Image* background;
    /*Button* Dungeon;
    Button* play;
    Button* pp;
    Button* donjon;
    Button* quest;
    Button* shop;
    Button* options;
    Button* Upgrades;*/

    int selected_tab;
} InGameMenu;

InGameMenu* inGameMenuCreate(SDL_Renderer* renderer, GameSettings* settings);
void destroyInGameMenu(InGameMenu* menu);
InGameMenuAction getSelectedActionInGameMenu(InGameMenu* menu);
#endif