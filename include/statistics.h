#ifndef STATS_H
#define STATS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int max_hp;
    int atk;
    int def;
    int speed;
    int atk_speed;
} Statistics;

Statistics* InitBasicStats();
void destroyStatistics(Statistics* stats);

#endif