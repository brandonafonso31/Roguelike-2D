#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdlib.h>
#include "paths.h"
#include "image_loader.h"

typedef struct {
    SDL_Rect rect;
    Image* normal_image;
    Image* click_image;
    Image* hover_image;
    char* text;
    int is_hovered;
} Button;

Button* createButtonWithText(Image* normal_image, Image* click_image, Image* hover_image, char* text, int x, int y, int w, int h);
Button* createButton(Image* normal_image, Image* click_image, Image* hover_image, int x, int y, int w, int h);
void destroyButton(Button* button);
void drawButtonRatio(SDL_Renderer* renderer, Button* button, double ratio);
void drawButton(SDL_Renderer* renderer, Button* button);
double getButtonHeight(Button* button);

#endif