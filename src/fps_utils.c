#include "fps_utils.h"

void FPSCounter_Init(FPSCounter* counter, int fps_limit) {
    counter->targetFrameTime = 1.0 / fps_limit;
    for (int i = 0; i < FPS_HISTORY; i++)
        counter->history[i] = counter->targetFrameTime;
    counter->index = 0;
    counter->lastFrameTime = 0;
}

double FPSCounter_GetDeltaTime(FPSCounter* counter) {
    Uint64 currentTime = SDL_GetPerformanceCounter();
    double deltaTime;
    
    if (counter->lastFrameTime == 0) {
        deltaTime = counter->targetFrameTime; // Premier frame
    } else {
        deltaTime = (double)(currentTime - counter->lastFrameTime) / SDL_GetPerformanceFrequency();
        // Limiter le deltaTime pour éviter les sauts trop grands (ex: après une pause)
        if (deltaTime > 0.1) deltaTime = counter->targetFrameTime;
    }
    
    counter->lastFrameTime = currentTime;
    return deltaTime;
}

int FPSCounter_Update(FPSCounter* counter, double deltaTime) {
    counter->history[counter->index] = deltaTime;
    counter->index = (counter->index + 1) % FPS_HISTORY;
    
    double sum = 0;
    for (int i = 0; i < FPS_HISTORY; i++)
        sum += counter->history[i];
    
    double averageDelta = sum / FPS_HISTORY;
    return (int)(0.5 + 1.0 / averageDelta);
}

void FPSCounter_WaitForNextFrame(FPSCounter* counter) {
    if (counter->targetFrameTime <= 0) return;
    
    Uint64 currentTime = SDL_GetPerformanceCounter();
    double elapsed = (double)(currentTime - counter->lastFrameTime) / SDL_GetPerformanceFrequency();
    
    if (elapsed < counter->targetFrameTime) {
        Uint32 waitMs = (Uint32)((counter->targetFrameTime - elapsed) * 1000);
        if (waitMs > 1) {
            SDL_Delay(waitMs - 1); // -1 pour éviter de dépasser
        }
        
        while (elapsed < counter->targetFrameTime) {
            currentTime = SDL_GetPerformanceCounter();
            elapsed = (double)(currentTime - counter->lastFrameTime) / SDL_GetPerformanceFrequency();
        }
    }
}

int GetMonitorRefreshRate() {
    SDL_DisplayMode mode;
    if (SDL_GetCurrentDisplayMode(0, &mode) == 0) {
        return mode.refresh_rate;
    }
    return -1; // Valeur par défaut si on ne peut pas récupérer
}

void wait_or_not(FPSCounter* fps_counter, GameSettings* settings){
    if (!settings->vsync) {
        FPSCounter_WaitForNextFrame(fps_counter);
    } else {
        SDL_Delay(1); // Petit délai pour éviter de surcharger le CPU
    }
}