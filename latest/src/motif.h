#ifndef _MOTIF_H_
#define _MOTIF_H_
#define MAX_MOTIF 5
#include "tile.h"
#include "players.h"

struct tile {
  struct color* tile_colors[4];
};

struct motif{
    struct tile motiff[MAX_MOTIF][MAX_MOTIF];
    int distance;
    int score_motif;
    int rank;
};


struct motif square();
struct motif heart();


#endif 
