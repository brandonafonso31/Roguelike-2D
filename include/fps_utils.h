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

void fpsCounterInit(FPSCounter* counter, int fps_limit);
double fpsCounterGetDeltaTime(FPSCounter* counter);
int fpsCounterUpdate(FPSCounter* counter, double dt);
void fpsCounterWaitForNextFrame(FPSCounter* counter);
int getMonitorRefreshRate(void);
void waitOrNot(FPSCounter* fps_counter, GameSettings* settings);

#endif