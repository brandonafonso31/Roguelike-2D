#include "menu.h"

MainMenu* menuCreate(SDL_Renderer* renderer, GameSettings* settings) {
    MainMenu* menu = (MainMenu*)malloc(sizeof(MainMenu));
    if (!menu) return NULL;

    menu->background = loadImageMenu(renderer, "background.jpg");
    menu->cursor = loadImageSystem(renderer, "cursor.png");
    
    menu->selected_index = 0;
    menu->button_count = MAX_BUTTONS;
    
    return menu;
}

void destroyMenu(MainMenu* menu) {
    if (!menu) return;
    
    destroyImage(menu->background);
    destroyImage(menu->cursor);
    menu->selected_index = -1;
    
    free(menu);
}

MainMenuAction getSelectedActionMenu(MainMenu* menu) {
    if (!menu) return MENU_QUIT;
        
    switch(menu->selected_index) {
        case 0: return MENU_NEW_GAME;
        case 1: return MENU_LOAD_GAME;
        case 2: return MENU_SETTINGS;
        case 3: return MENU_QUIT;
        default: return MENU_LOAD_GAME; //if save else MENU_NEW_GAME;
    }
}

InGameMenu* inGameMenuCreate(SDL_Renderer* renderer, GameSettings* settings) {
    InGameMenu* menu = (InGameMenu*)malloc(sizeof(InGameMenu));
    if (!menu) return NULL;

    menu->background = loadImageMenu(renderer, "world1.png");
    
    /*Button* Dungeon = NULL;
    Button* play = NULL;
    Button* pp = NULL;
    Button* donjon = NULL;
    Button* quest = NULL;
    Button* shop = NULL;
    Button* options = NULL;
    Button* Upgrades = NULL;*/
    
    menu->selected_tab = 2;
    menu->button_count = 5;
    
    return menu;
}

void destroyInGameMenu(InGameMenu* menu) {
    if (!menu) return;
    
    destroyImage(menu->background);
    
    free(menu);
}

InGameMenuAction getSelectedActionInGameMenu(InGameMenu* menu) {
    if (!menu) return MENU_QUIT;
        
    switch(menu->selected_tab) {
        case 0: return SHOP;
        case 1: return INVENTORY;
        case 2: return WORLD;
        case 3: return UPGRADES;
        case 4: return WIP;

        case 5: return INGAME_PLAY;
        case 6: return INGAME_BACK;
        case 7: return INGAME_QUIT;
        default: return WORLD;
    }
}