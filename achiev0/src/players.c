#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "tile.h"
#include "queue.h"
#include "players.h"
#include <string.h>

struct players players_init(int n){
  if (n > MAX_PLAYERS){
    printf("Error: maximum number of players exceeded\n");
    exit(EXIT_FAILURE);
  }  
  struct players p;
  p.length = n;
  for (int i=0; i<p.length; i++){
    p.player[i].cards = initQueue();  
  }
  p.rank = 0;
  return p;
}


struct board board_init(int b){
  if (b > MAX_BOARD_SIZE){
    printf("Error max board size exceeded\n");
    exit(EXIT_FAILURE);
  }
  struct board playboard;
  for (int i=0; i<b; i++){
    for (int j=0; j<b; j++){
      (playboard.places)[i][j] = empty_tile();
    }
  }
  playboard.size = b;
  return playboard;
}

struct player get_next_player(struct players *p)
{
  if (p->rank == p->length)
  {
    p->rank = 1;
    return p->player[0];
  }
  p->rank ++;
  return p->player[p->rank-1];
}

void split_deck(struct deck *d, struct players *p){
  int selec_p =0;
  unsigned int selec_t =0;
  int selec_c =0;
  int q = (d->size)/(p->length);
  int r = (d->size)%(p->length);
  int L[p->length];
  for (int i=0; i<(p->length); i++){
    L[i] = q + (r > 0);
    r = r-1;
  }
  for (unsigned int i=0; i<(d->size); i++){
    selec_p = rand()%(p->length);
    while (L[selec_p] == 0){
      selec_p = (selec_p+1)%(p->length);
    }
    selec_t = i;
    selec_c = 0;
    while (selec_t>=(d->cards[selec_c].n)){
      selec_t = selec_t - d->cards[selec_c].n;
      selec_c++;
    }
    printf("le joueur %d obtient une carte\n",selec_p);
    push((p->player[selec_p]).cards, (d->cards)[selec_c].t);    
    L[selec_p] = L[selec_p]-1;
  }
  for (int i=0; i<(p->length); i++)
    {
      p->player[i].cards = rand_q(p->player[i].cards);
    }
}


int oppose_Direction(int n)
{
  if (n == NORTH)
    return SOUTH;
  else if (n == SOUTH)
    return NORTH;
  else if (n == EAST)
    return WEST;
  else if (n == WEST)
    return EAST;
  else
    return -1;
}

struct positions list_authorized_places(struct board *b, const struct tile *t){  
  struct positions pos;
  const struct tile* adj[4];
  pos.length = 0;
  int bool = 1;  
  int empty = 1;
  for (int k=0; k<b->size; k++){
    for (int l=0; l<b->size; l++){
      adj[NORTH] = empty_tile();
      adj[EAST] = empty_tile();
      adj[SOUTH] = empty_tile();
      adj[WEST] = empty_tile();
      bool = 1;
      bool = bool && tile_is_empty(b->places[k][l]);
      empty = empty && tile_is_empty(b->places[k][l]);
      if ((k > 0) && bool)
        adj[NORTH] = b->places[k-1][l];
      if ((k<b->size-1) && bool)
        adj[SOUTH] = b->places[k+1][l];
      if ((l > 0) && bool)
        adj[WEST] = b->places[k][l-1];
      if ((l<b->size-1) && bool)
        adj[EAST] = b->places[k][l+1];
      
      bool = bool && !(tile_is_empty(adj[NORTH]) && tile_is_empty(adj[SOUTH]) && tile_is_empty(adj[EAST]) && tile_is_empty(adj[WEST]));
      for (int dir = 0; dir<4; dir++){
        if (!tile_is_empty(adj[dir])){
          bool = bool && (tile_edge(adj[dir],oppose_Direction(dir)) == tile_edge(t,dir));
        }
      }
      if (bool){
        pos.i[pos.length] = k;
        pos.j[pos.length] = l;
        pos.length += 1;
      }
    }
  }
  if (empty){
    for (int k=0; k<b->size; k++){
      for (int l=0; l<b->size; l++){
        pos.i[k*(b->size)+l] = k;
        pos.j[k*(b->size)+l] = l;
      }
    }
    pos.length = (b->size)*(b->size);
    return pos;
  }
  return pos;
}

int is_empty(struct positions *p)
{
  return (p->length==0);
}

struct positions select_position(struct positions p)
{
  struct positions pos;
  int k = rand() % p.length;
  pos.i[0]= p.i[k];
  pos.j[0]= p.j[k];
  pos.length = 1;
  return pos;
}

void place_tile(struct board *b, struct positions p, const struct tile *t)
{
  b->places[p.i[0]][p.j[0]] = t;
  printf("le joueur a placé une tuile en (%d,%d)\n",p.i[0],p.j[0]);
}

void display_results(struct players *p)
{
  int counter = 0;
  for (int i =0; i< p->length ;i++)
  {
    if (top(p->player[i].cards) == NULL)
    {
      printf("\n \nle joueur %d n'a plus de carte\n",i);
      printf("le joueur %d a gagné.\n",i);
      counter++;
    }
  }
  if (counter == 0)
    printf("plus personne ne peut poser de tuiles : persone n'a gagné.\n");
}

void freeAll(struct players *p){
  for (int i=0; i < p->length; i++){
    popAll(p->player[i].cards);
    free(p->player[i].cards);
  } 
}
