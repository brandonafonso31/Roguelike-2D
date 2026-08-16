#ifndef DRAWING_FUNCTION_H
#define DRAWING_FUNCTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "paths.h"

void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
void drawTextWhite(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);
void drawTextGray(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);
void drawTextBlack(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);
SDL_Color readColor(const char* color_name);
void drawTriangle(int x, int y, SDL_Renderer* renderer, int width);
void drawColoredTriangle(int x, int y, SDL_Renderer* renderer, int width, const char* color_name);

#endif