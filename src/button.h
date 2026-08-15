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
    char* text;
} Button;

Button* createButton(Image* normal_image, Image* click_image, char* text, int x, int y, int w, int h);

#endif