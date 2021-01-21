#include <stdio.h>
#include <stdlib.h>

#include "tile.h"
#include "color.h"

struct tile {
  struct color* tile_colors[4];
};


static struct tile deck_tiles[MAX_DECK_SIZE];

// A tile that is empty
const struct tile* empty_tile(){
  const struct tile* t=NULL;
  return t;
}

// A predicate telling if the tile is empty
int tile_is_empty(const struct tile* t){
  return (NULL  == t);
}

// A comparator between tiles
int tile_equals(const struct tile* t1, const struct tile* t2){
  int rep = 1;
  for (int i = 0; i<4 ; i++){
    rep = rep * ((t1->tile_colors)[i] == (t2->tile_colors)[i]);
  }
  return rep;
}


// Accessors to the color of the edges
struct color* tile_edge(const struct tile* t, enum direction d){
  if (t==NULL)
    return NULL;
  return (t->tile_colors)[d];
}


// A function that fills a deck with tiles
void deck_init(struct deck* d){
  const struct tile t1 = {{ color_from_name("Red"),color_from_name("Red"),color_from_name("Red"),color_from_name("Red") }};
  const struct tile t2 = {{ color_from_name("Red"),color_from_name("Black"),color_from_name("Red"),color_from_name("Red") }};
  deck_tiles[0] = t1;
  deck_tiles[1] = t2;
  struct deck_pair p1 = { &deck_tiles[0],6 };
  struct deck_pair p2 = { &deck_tiles[1],2 };
  d->cards[0] = p1;
  d->cards[1] = p2;
  d->size = 8;
}

