#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include "settings.h"
#include "image.h"
#include "button.h"

typedef enum {
    MENU_NEW_GAME,
    MENU_LOAD_GAME,
    MENU_SETTINGS,
    MENU_QUIT
} MainMenuAction;

#define MAIN_MENU_BUTTONS \
    X(newgame, MENU_NEW_GAME) \
    X(continue_game, MENU_LOAD_GAME) \
    X(settings, MENU_SETTINGS) \
    X(quit, MENU_QUIT) \
    //X(test_button, MENU_QUIT)

typedef struct {
    #define X(name, action) Button* name;
    MAIN_MENU_BUTTONS
    #undef X
} MainMenuButtons;

#define NUMBER_OF_MAINMENU_BUTTONS (int)(sizeof(MainMenuButtons) / sizeof(Button*))
MainMenuButtons* initMainMenuButtons(SDL_Renderer* renderer, GameSettings* settings);

typedef struct {
    Image* background;
    Image* cursor;

    MainMenuButtons* buttons;

    int selected_index;
    int button_count;
} MainMenu;

MainMenu* menuCreate(SDL_Renderer* renderer, GameSettings* settings);
void destroyMenu(MainMenu* menu);
MainMenuAction getSelectedActionMenu(MainMenu* menu);
void changeButtonFromIndex(MainMenu* menu, int index);

typedef enum {
    SHOP,
    INVENTORY,
    WORLD,
    UPGRADES,
    WIP,
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
    int last_tab_id;
    int nb_tabs;
} InGameMenu;

InGameMenu* inGameMenuCreate(SDL_Renderer* renderer, GameSettings* settings);
void destroyInGameMenu(InGameMenu* menu);
InGameMenuAction getSelectedActionInGameMenu(InGameMenu* menu);

typedef struct {
    //Image* cursor; (not sure if using it or not)
    //todo : scroll bar to change volume
    Image* background;

    int selected_tab;
    int nb_tabs;
} SettingsMenu;

SettingsMenu* settingsMenuCreate(SDL_Renderer* renderer, GameSettings* settings);
void destroySettingsMenu(SettingsMenu* menu);

#endif