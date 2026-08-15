// image_loader.h
#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "paths.h"


typedef struct {
    SDL_Texture* texture;
    int width;
    int height;
} Image;

// Charger une image depuis le dossier assets/images/
Image* LoadImage(SDL_Renderer* renderer, const char* path);
void DestroyImage(Image* image);
void RenderImage(SDL_Renderer* renderer, Image* image, int x, int y);
void RenderImageOrigin(SDL_Renderer* renderer, Image* image);
void RenderScaledImage(SDL_Renderer* renderer, Image* image, int x, int y, int w, int h);
void RenderScaledImageOrigin(SDL_Renderer* renderer, Image* image, int w, int h);

void RenderScaledWidthImage(SDL_Renderer* renderer, Image* image, int x, int y, int w);
void RenderScaledHeightImage(SDL_Renderer* renderer, Image* image, int x, int y, int h);
void RenderScaledWidthImageOrigin(SDL_Renderer* renderer, Image* image,  int w);
void RenderScaledHeightImageOrigin(SDL_Renderer* renderer, Image* image,  int h);

#endif