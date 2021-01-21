#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "color.h"
#include "tile.h"
#include "players.h"
#include "motif.h"
#define MAX_STR 100

// Global seed for the random number generator
int seed = 0;
// Board size 
unsigned int boardSize = 10;
// number of players in the game
unsigned int playersNumber = 2;
////////////////////////////////////////////////////////////////
// Function for parsing the options of the program
// Currently available options are :
// -s <seed> : sets the seed
void parse_opts(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "s:n:b:")) != -1) {
    switch (opt) 
    {
      case 's':
        seed = atoi(optarg);
        break;
      case 'b':
        boardSize = atoi(optarg);        
        break;
      case 'n':
        playersNumber = atoi(optarg);
        break;

      default: /* '?' */
      fprintf(stderr, "Usage: %s [-s seed] \n",
              argv[0]);

      exit(EXIT_FAILURE);
    }
  }
}


//////////////////////////////////////////////////////////
int main(int argc,  char* argv[]) {
  parse_opts(argc, argv);
  printf("Seed : %d\n", seed);
  srand(seed);
  int skip = 0;
  struct deck d;
  struct board b;
  struct players players;
  struct player active_player;
  struct positions p;
  const struct tile *t = NULL;
  deck_init(&d);
  b = board_init(boardSize);
  players = players_init(playersNumber);
  int n = players.length;
  split_deck(&d,&players);
  while (skip < n)
  {
    active_player = get_next_player(&players);
    printf("\n \n");
    printf("le joueur %d joue...\n",players.rank-1);
    if (top(active_player.cards) == NULL)
      break;
    t = top(players.player[players.rank-1].cards)->tile;
    p = list_authorized_places(&b,t);
    if (!is_empty(&p))
    {
      place_tile(&b,select_position(p),t,&players);
      //printf("%d %d", players.player[players.rank-1].playertiles.i[players.player[players.rank-1].playertiles.length-1],players.player[players.rank-1].playertiles.j[players.player[players.rank-1].playertiles.length-1]);
      pop(players.player[players.rank-1].cards);
      if (top(players.player[players.rank-1].cards) == NULL)
        break;
      skip = 0;
    }
    else
    {
      skip++;
      printf(" ce tour est skip %d\n",skip);
    }
  }
  //int x = players.player[0].playertiles.i[2];
  //int y = players.player[0].playertiles.j[2];
  //printf("%d\n",players.player[0].playertiles.length);
  //printf("%s\n",color_name(tile_edge(b.places[x][y],NORTH)));        
  display_results(&players,&b);
  freeAll(&players);
  //
  //struct tile t1 = {{ &Red,&Black,&Black,&Black }};
  //struct tile t2 = {{ &White,&Red,&White,&White }};
  //
//
  //struct board b;
  //b = board_init(boardSize);
  //b.places[1][0]= &t1;
 //// b.places[5][5]= &t2;
  //
  //struct positions pos;
  //pos = list_authorized_places(&b,&t2);
  //printf("%d\n",select_position(pos).length);
//
  //place_tile(&b, select_position(pos),&t2);
  //printf("%d\n", b.places[0][1]==&t2);
//
  //
  //struct positions p;
  //p.i[0]= 1;
  //p.i[1]= 2;
  //p.j[0]= 1;
  //p.j[1]= 3;
  //p.length = 2;
//
//
//
  return EXIT_SUCCESS;
}