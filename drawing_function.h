#ifndef DRAWING_FUNCTION_H
#define DRAWING_FUNCTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);

#endif