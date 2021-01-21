#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "color.h"
#include "tile.h"
#include "players.h"
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

struct tile {
  struct color* tile_colors[4];
};

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
  const struct tile *t;
 
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
      place_tile(&b,select_position(p),t);
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

  display_results(&players);
  freeAll(&players);

  return EXIT_SUCCESS;
}

