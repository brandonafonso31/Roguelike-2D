#include "statistics.h"

Statistics* setBasicStats(){
    Statistics* stats = (Statistics*)malloc(sizeof(Statistics));
    if (!stats) {
        printf("Erreur allocation des statistiques\n");
        return NULL;
    }
    stats->hp = 1;
    stats->atk = 1;
    stats->def = 1;
    stats->speed = 1;
    stats->atk_speed = 1;

    return stats;
}

void destroyStatistics(Statistics* stats) {
    if (stats) {
        free(stats);
    }
}