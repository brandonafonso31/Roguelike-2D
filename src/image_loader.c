#include "image_loader.h"

Image* LoadImage(SDL_Renderer* renderer, const char* path) {
    if (!renderer) {
        printf("Erreur: renderer NULL\n");
        return NULL;
    }
    
    char full_path[2048];
    snprintf(full_path, sizeof(full_path), "%s/%s", GetImagesPath(), path);
    
    SDL_Surface* surface = IMG_Load(full_path);
    if (!surface) {
        printf("Erreur chargement %s: %s\n", full_path, IMG_GetError());
        return NULL;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur création texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }
    
    Image* image = (Image*)malloc(sizeof(Image));
    image->texture = texture;
    image->width = surface->w;
    image->height = surface->h;
    
    SDL_FreeSurface(surface);
    
    printf("Image chargée: %s (%dx%d)\n", full_path, image->width, image->height);
    return image;
}

void DestroyImage(Image* image) {
    if (image) {
        if (image->texture) {
            SDL_DestroyTexture(image->texture);
        }
        free(image);
    }
}

void RenderImage(SDL_Renderer* renderer, Image* image, int x, int y) {
    if (!image || !image->texture) return;
    
    SDL_Rect dest = {x, y, image->width, image->height};
    SDL_RenderCopy(renderer, image->texture, NULL, &dest);
}

void RenderImageOrigin(SDL_Renderer* renderer, Image* image) {
    RenderImage(renderer, image, 0, 0);
}

void RenderScaledImage(SDL_Renderer* renderer, Image* image, int x, int y, int w, int h) {
    if (!image || !image->texture) return;
    
    SDL_Rect dest = {x, y, w, h};
    SDL_RenderCopy(renderer, image->texture, NULL, &dest);
}

void RenderScaledImageOrigin(SDL_Renderer* renderer, Image* image, int w, int h) {
    if (!image || !image->texture) return;
    
    SDL_Rect dest = {0, 0, w, h};
    SDL_RenderCopy(renderer, image->texture, NULL, &dest);
}

void RenderScaledWidthImage(SDL_Renderer* renderer, Image* image, int x, int y, int w) {
    if (!image || !image->texture) return;
    
    SDL_Rect dest = {x, y, w, w * image->height / image->width};
    SDL_RenderCopy(renderer, image->texture, NULL, &dest);
}

void RenderScaledWidthImageOrigin(SDL_Renderer* renderer, Image* image,  int w) {
    RenderScaledWidthImage(renderer, image, 0, 0, w) ;
}

void RenderScaleHeightImage(SDL_Renderer* renderer, Image* image, int x, int y, int h) {
    if (!image || !image->texture) return;

    SDL_Rect dest = {x, y, h * image->width / image->height, h};
    SDL_RenderCopy(renderer, image->texture, NULL, &dest);
}

void RenderScaledHeightImageOrigin(SDL_Renderer* renderer, Image* image,  int h) {
    RenderScaleHeightImage(renderer, image, 0, 0, h) ;
}