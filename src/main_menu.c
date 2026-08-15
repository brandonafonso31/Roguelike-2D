#include "main_menu.h"

MainMenu* Menu_Create(SDL_Renderer* renderer) {
    MainMenu* menu = (MainMenu*)malloc(sizeof(MainMenu));
    if (!menu) return NULL;

    menu->background = Image_Load(renderer, "menu/background.png");
    /*menu->title = Image_Load(renderer, "menu/title.png");
    menu->play_button = Image_Load(renderer, "menu/buttons/play.png");
    menu->settings_button = Image_Load(renderer, "menu/buttons/settings.png");
    menu->quit_button = Image_Load(renderer, "menu/buttons/quit.png");
    
    menu->play_button_hover = Image_Load(renderer, "menu/buttons/play_hover.png");
    menu->settings_button_hover = Image_Load(renderer, "menu/buttons/settings_hover.png");
    menu->quit_button_hover = Image_Load(renderer, "menu/buttons/quit_hover.png");*/
    
    menu->selected_index = 0;
    menu->button_count = 3;
    
    return menu;
}

void Menu_Destroy(MainMenu* menu) {
    if (!menu) return;
    
    Image_Destroy(menu->background);
    
    /*Image_Destroy(menu->title);
    Image_Destroy(menu->play_button);
    Image_Destroy(menu->settings_button);
    Image_Destroy(menu->quit_button);
    Image_Destroy(menu->play_button_hover);
    Image_Destroy(menu->settings_button_hover);
    Image_Destroy(menu->quit_button_hover);*/
    
    free(menu);
}

void main_menu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings) {

    int running = 1;
    SDL_Event event;
    char font_full_path[2048];
    snprintf(font_full_path, sizeof(font_full_path), "%s/%s", GetFontsPath(), settings->font);
    TTF_Font* font = TTF_OpenFont(font_full_path, 24);
    if (!font) {
        printf("Erreur chargement police : %s\n", TTF_GetError());
        return;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Erreur IMG_Init: %s\n", IMG_GetError());
        return;
    }
    
    MainMenu* menu = Menu_Create(renderer);
    if (!menu) {
        printf("Erreur création du menu\n");
        return;
    }

    FPSCounter fps_counter;
    FPSCounter_Init(&fps_counter, settings->fps_limit);
    double dt;

    while (running) {
        //---------------- INPUT ----------------//
        running = poll_events(&event);
        //---------------- Delta ----------------//
        dt = FPSCounter_GetDeltaTime(&fps_counter);
        //---------------- RENDER ---------------//
        render_main_menu_ui(&fps_counter, renderer, dt, font, settings);
        //---------------- FPS LIMIT ----------------//
        wait_or_not(&fps_counter, settings);
    }

    TTF_CloseFont(font);
}