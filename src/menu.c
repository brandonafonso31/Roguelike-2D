#include "menu.h"

MainMenuButtons* initMainMenuButtons(SDL_Renderer* renderer, GameSettings* settings) {
    MainMenuButtons* buttons = (MainMenuButtons*)malloc(sizeof(MainMenuButtons));
    if (!buttons) return NULL;
        
    Image* image_newgame = loadImageMenu(renderer, "newgame.png");
    int width = image_newgame->width/3, height = image_newgame->height/3;
    int screen_w = settings->width;
    int screen_h = settings->height;
    int center_x = screen_w - width - 10;
    int start_y = screen_h / 2;
    int spacing = height + 5;

    buttons->newgame = createButton(
        image_newgame,
        loadImageMenu(renderer, "newgame_clicked.png"),
        loadImageMenu(renderer, "newgame_hover.png"),
        center_x, start_y, width, height
    );
    
    buttons->continue_game = createButton(
        loadImageMenu(renderer, "continue.png"),
        loadImageMenu(renderer, "continue_clicked.png"),
        loadImageMenu(renderer, "continue_hover.png"),
        center_x, start_y + spacing, width, height
    );
    
    buttons->settings = createButton(
        loadImageMenu(renderer, "settings.png"),
        loadImageMenu(renderer, "settings_clicked.png"),
        loadImageMenu(renderer, "settings_hover.png"),
        center_x, start_y + 2 * spacing, width, height
    );
    
    buttons->exit = createButton(
        loadImageMenu(renderer, "exit.png"),
        loadImageMenu(renderer, "exit_clicked.png"),
        loadImageMenu(renderer, "exit_hover.png"),
        center_x, start_y + 3 * spacing, width, height
    );
    
    return buttons;
}

MainMenu* menuCreate(SDL_Renderer* renderer, GameSettings* settings) {
    MainMenu* menu = (MainMenu*)malloc(sizeof(MainMenu));
    if (!menu) return NULL;

    menu->background = loadImageMenu(renderer, "background.jpg");
    menu->cursor = loadImageSystem(renderer, "cursor.png");
    
    menu->buttons = initMainMenuButtons(renderer, settings);
    menu->selected_index = 0;
    menu->button_count = MAX_BUTTONS;
    
    return menu;
}

void changeButtonFromIndex(MainMenu* menu, int index) {
    if (!menu || !menu->buttons) return;

    MainMenuButtons* buttons = menu->buttons;
    buttons->newgame->is_hovered = 0;
    buttons->continue_game->is_hovered = 0;
    buttons->settings->is_hovered = 0;
    buttons->exit->is_hovered = 0;
    
    switch (index) {
        case 0:
            buttons->newgame->is_hovered = 1;
            break;
        case 1:
            buttons->continue_game->is_hovered = 1;
            break;
        case 2:
            buttons->settings->is_hovered = 1;
            break;
        case 3:
            buttons->exit->is_hovered = 1;
            break;
        default:
            break;
    }
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
    menu->last_tab_id = 2;
    menu->nb_tabs = 5;
    
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