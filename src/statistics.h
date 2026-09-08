#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int hp;
    int atk;
    int def;
    int speed;
    int atk_speed;
} Statistics;

Statistics* setBasicStats();
void destroyStatistics(Statistics* stats);

#endif