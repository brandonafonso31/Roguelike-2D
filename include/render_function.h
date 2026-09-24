#ifndef DRAWING_FUNCTION_H
#define DRAWING_FUNCTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "paths.h"

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
void renderTextWhite(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);
void renderTextGray(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);
void renderTextBlack(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y);
SDL_Color readColor(const char* color_name);
void renderTriangle(int x, int y, SDL_Renderer* renderer, int width);
void renderColoredTriangle(int x, int y, SDL_Renderer* renderer, int width, const char* color_name);
//void renderPlayer(Entity* player);

#endif