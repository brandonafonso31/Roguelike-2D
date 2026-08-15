#include "menu.h"

MainMenu* menuCreate(SDL_Renderer* renderer, GameSettings* settings) {
    MainMenu* menu = (MainMenu*)malloc(sizeof(MainMenu));
    if (!menu) return NULL;

    menu->background = loadImageMenu(renderer, "background.jpg");
    menu->cursor = loadImageMenu(renderer, "cursor.png");
    
    menu->selected_index = -1;
    menu->button_count = MAX_BUTTONS;
    
    return menu;
}

void destroyMenu(MainMenu* menu) {
    if (!menu) return;
    
    destroyImage(menu->background);
    
    free(menu);
}

    MenuAction getSelectedActionMenu(MainMenu* menu) {
        if (!menu) return MENU_QUIT;
        
        switch(menu->selected_index) {
            case 0: return MENU_NEW_GAME;
            case 1: return MENU_SETTINGS;
            case 2: return MENU_QUIT;
            default: return MENU_LOAD_GAME; //if save else MENU_NEW_GAME;
        }
    }