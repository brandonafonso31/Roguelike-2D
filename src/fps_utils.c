#include "fps_utils.h"

void FPSCounter_Init(FPSCounter* counter, int fps_limit) {
    counter->target_frame_time = 1.0 / fps_limit;
    for (int i = 0; i < FPS_HISTORY; i++)
        counter->history[i] = counter->target_frame_time;
    counter->index = 0;
    counter->last_frame_time = 0;
}

double FPSCounter_GetDeltaTime(FPSCounter* counter) {
    Uint64 currentTime = SDL_GetPerformanceCounter();
    double dt;
    
    if (counter->last_frame_time == 0) {
        dt = counter->target_frame_time; // Premier frame
    } else {
        dt = (double)(currentTime - counter->last_frame_time) / SDL_GetPerformanceFrequency();
        // Limiter le deltaTime pour éviter les sauts trop grands (ex: après une pause)
        if (dt > 0.1) dt = counter->target_frame_time;
    }
    
    counter->last_frame_time = currentTime;
    return dt;
}

int FPSCounter_Update(FPSCounter* counter, double dt) {
    counter->history[counter->index] = dt;
    counter->index = (counter->index + 1) % FPS_HISTORY;
    
    double sum = 0;
    for (int i = 0; i < FPS_HISTORY; i++)
        sum += counter->history[i];
    
    double average_dt = sum / FPS_HISTORY;
    return (int)(0.5 + 1.0 / average_dt);
}

void FPSCounter_WaitForNextFrame(FPSCounter* counter) {
    if (counter->target_frame_time <= 0) return;
    
    Uint64 current_time = SDL_GetPerformanceCounter();
    double elapsed = (double)(current_time - counter->last_frame_time) / SDL_GetPerformanceFrequency();
    
    if (elapsed < counter->target_frame_time) {
        Uint32 wait_ms = (Uint32)((counter->target_frame_time - elapsed) * 1000);
        if (wait_ms > 1) {
            SDL_Delay(wait_ms - 1); // -1 pour éviter de dépasser
        }
        
        while (elapsed < counter->target_frame_time) {
            current_time = SDL_GetPerformanceCounter();
            elapsed = (double)(current_time - counter->last_frame_time) / SDL_GetPerformanceFrequency();
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