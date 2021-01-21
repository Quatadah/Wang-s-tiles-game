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
unsigned int boardSize = 3;
// number of players in the game
unsigned int playersNumber = 1;
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

static struct tile deck_tiles[MAX_DECK_SIZE];


static void deck_init2(struct deck* d){
  const struct tile t1 = {{ color_from_name("Red"),color_from_name("Red"),color_from_name("Red"),color_from_name("Red") }};
  const struct tile t2 = {{ color_from_name("Red"),color_from_name("Black"),color_from_name("Red"),color_from_name("Red") }};
  deck_tiles[0] = t1;
  deck_tiles[1] = t2;
  struct deck_pair p1 = { &deck_tiles[0],9 };
  struct deck_pair p2 = { &deck_tiles[1],0 };
  d->cards[0] = p1;
  d->cards[1] = p2;
  d->size = 9;
}


//////////////////////////////////////////////////////////
int main(int argc,  char* argv[]) {
  parse_opts(argc, argv);
  printf("Seed : %d\n", seed);
  srand(seed);
  
  printf("****** test le nouveau display_results ******\n");
  printf("Dans ce test, on va changer deck_init de telle façon de prevoir le resultat, ainsi on verra si la fonction display_results affichera la meme chose.\n");
  
  // Rajouter ceci dans le rapport : 
    /*
      On a limité le boardSize à 3x3, et on a laissé un seul joueur, puis on lui a distribué 9 tuiles
      semblables remplies de la même couleur dans toutes les directions. De plus, on sait que pour avoir 
      le motif coeur il faut 7 tuiles de la même couleur placé sous forme d'un carré, donc la seule 
      possibilité pour le joueur quelque soit la combinaison avec laquelle il pose ses tuiles, il finira
      par arriver à faire le motif coeur et seulement lui. D'où, son score finale sera bien celui du 
      coeur à savoir 60.

      Si on fait pareil pour BoardSize (4 x 4) et on distribuant 16 tuiles à l'unique joueur, il finira
      par arriver à faire 4 coeurs, son score finale serait donc de 240 = 60 * 4.

    */
  int skip = 0;
  struct deck d;
  struct board b;
  struct players players;
  struct player active_player;
  struct positions p;
  const struct tile *t = NULL;
  deck_init2(&d);
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
      //printf(" ce tour est skip %d\n",skip);
    }
  }
  //int x = players.player[0].playertiles.i[2];
  //int y = players.player[0].playertiles.j[2];
  //printf("%d\n",players.player[0].playertiles.length);
  //printf("%s\n",color_name(tile_edge(b.places[x][y],NORTH)));        
  display_results(&players,&b);
  freeAll(&players);

  //struct motif m1 = heart();
  //struct tile t1 = {{ color_from_name("Red"),color_from_name("Red"),color_from_name("Red"),color_from_name("Red")}};
  //struct players players = players_init(2);
  //struct board b = board_init(5);

  //struct motif m2 = square();
//
  //printf("%d\n",tile_edge(&m1.motiff[0][0],SOUTH) == color_from_name("White"));
  ////doit afficher 1
//
  //struct board board;
  //board = board_init(3);
//
  //struct color *b = color_from_name("RED");
  //struct color *w = color_from_name("Blue");
  //struct tile t1 = {{ b,w,w,b }};
  //struct tile t2 = {{ b,w,w,w }};
  //struct tile t3 = {{ b,w,b,w }};
  //struct tile t4 = {{ w,b,w,b }};
  //struct tile t5 = {{ w,w,w,w }};
  //struct tile t6 = {{ w,b,b,w }};
  //struct tile t7 = {{ b,b,b,b }};
  //struct tile t8 = {{ w,b,b,b }};
  //board.places[0][0] = &t1;
  //board.places[0][1] = &t2;
  //board.places[0][2] = &t3;
  //board.places[1][0] = &t4;
  //board.places[1][1] = &t5;
  //board.places[1][2] = &t6;
  //board.places[2][0] = &t7;
  //board.places[2][1] = &t8;
  //board.places[2][2] = &t7;
  //int m =0;
  //int x=1;
  //int y=1;
  //int bool = 1;
  //struct motif liste_motif[] = {heart(),square()};
  //struct color* c = tile_edge(board.places[x][y],NORTH);
  //for (int a=x-liste_motif[m].distance; a<x+liste_motif[m].distance +1 ;a++)
  //{
  //  for (int z=y-liste_motif[m].distance; z<y+liste_motif[m].distance +1 ;z++)
  //  {
  //    for (int d=0; d<4; d++)
  //    {
  //      if (tile_edge(&liste_motif[m].motiff[a-x+liste_motif[m].distance][z-y+liste_motif[m].distance],d) == color_from_name("White"))
  //      {
  //        bool = bool && (tile_edge(board.places[a][z],d) == c);
  //      }
  //    }
  //  }
  //}
  //printf("%d\n",bool);
  //doit renvoyé si il ya un coeur
}
