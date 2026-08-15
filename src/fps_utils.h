#ifndef FPS_UTILS_H
#define FPS_UTILS_H

#include <SDL2/SDL.h>
#include "settings.h"
#define FPS_HISTORY 30

typedef struct {
    double history[FPS_HISTORY];
    int index;
    double target_frame_time;
    Uint64 last_frame_time;
} FPSCounter;

void FPSCounter_Init(FPSCounter* counter, int fps_limit);
double FPSCounter_GetDeltaTime(FPSCounter* counter);
int FPSCounter_Update(FPSCounter* counter, double dt);
void FPSCounter_WaitForNextFrame(FPSCounter* counter);
int GetMonitorRefreshRate(void);
void wait_or_not(FPSCounter* fps_counter, GameSettings* settings);

#endif