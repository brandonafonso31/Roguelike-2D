#include "button.h"

Button* createButtonWithText(Image* normal_image, Image* click_image, Image* hover_image, char* text, int x, int y, int w, int h) {
    Button* button = (Button*)malloc(sizeof(Button));
    if (!button) {
        printf("Erreur: allocation mémoire pour Button échouée\n");
        return NULL;
    }
    
    button->rect.x = x;
    button->rect.y = y;
    button->rect.w = w;
    button->rect.h = h;

    button->normal_image = normal_image;
    button->click_image = click_image;
    button->hover_image = hover_image;

    button->text = text;
    button->is_hovered = 0;
    return button;
}

Button* createButton(Image* normal_image, Image* click_image, Image* hover_image, int x, int y, int w, int h){
    return createButtonWithText(normal_image, click_image, hover_image, "", x, y, w, h);
}

void destroyButton(Button* button) {
    if (!button) return;    
    destroyImage(button->normal_image);
    destroyImage(button->click_image);
    free(button);
}

void drawButton(SDL_Renderer* renderer, Button* button, double ratio){
    Image* button_image = (button->is_hovered) ? button->hover_image : button->normal_image;
    renderScaledRatioImage(renderer, button_image, button->rect.x, button->rect.y, ratio);
}