#include "menu.h"

MainMenu* menuCreate(SDL_Renderer* renderer, GameSettings* settings) {
    MainMenu* menu = (MainMenu*)malloc(sizeof(MainMenu));
    if (!menu) return NULL;

    menu->background = loadImageMenu(renderer, "background.jpg");
    
    menu->selected_index = -1;
    menu->button_count = MAX_BUTTONS;
    
    return menu;
}

void destroyMenu(MainMenu* menu) {
    if (!menu) return;
    
    destroyImage(menu->background);
    
    free(menu);
}