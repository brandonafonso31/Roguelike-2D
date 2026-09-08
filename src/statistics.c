#include "statistics.h"

Statistics* setBasicStats(){
    Statistics* stats;
    stats->hp = 1;
    stats->atk = 1;
    stats->def = 1;
    stats->speed = 1;
    stats->atk_speed = 1;

    return stats;
}