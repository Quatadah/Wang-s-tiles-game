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
struct color{
  const char name[MAX_STR];
  const char code[MAX_STR];
};
struct color Black={{"BLACK"},{"\\u001b[30m"}};
struct color Red={{"RED"},{"\\u001b[31m"}};
struct color Green={{"Green"},{"\\u001b[32m"}};
struct color Yellow={{"Yellow"},{"\\u001b[33m"}};
struct color Blue={{"Blue"},{"\\u001b[34m"}};
struct color White={{"White"},{"\\u001b[37m"}};
struct color Void={{"void"},{"void"}};

struct color *colors_table[6]={&Black,&Red,&Green,&Yellow,&Blue,&White};

struct tile {
  struct color* tile_colors[4];
};

struct tile deck_tiles[MAX_DECK_SIZE];
  

//////////////////////////////////////////////////////////
int main(int argc,  char* argv[]) {
  parse_opts(argc, argv);
  printf("Seed : %d\n", seed);
  srand(seed);

  printf(" ****** test pour le fichier color.c ******\n");
  printf("Renvoie le nom de la couleur <Green> : %s  \n",color_name(&Green));
  printf("Renvoie le code de la couleur <Black> : %s \n",color_cstring(&Black));
  printf("Renvoie le nom de la couleur <Red> appelee a partir de color_from_name : %s\n",color_name(color_from_name("Red")));

  printf("\n\n\n ****** test pour le fichier tile.c ******\n");
  struct tile t1 = {{ &Red,&Black,&Black,&Black }};
  struct tile t2 = {{ &White,&Red,&White,&White }};
  printf("teste empty_tile -> doit renvoyer (0,1) : %d,%d \n",empty_tile()== &t1,empty_tile()==NULL);
  printf("teste tile_is_empty -> doit renvoyer (0,1) : %d,%d\n", tile_is_empty(&t1),tile_is_empty(empty_tile()));
  printf("teste tile_equals -> doit renvoyer (0,1) : %d, %d \n",tile_equals(&t1,&t2),tile_equals(&t1,&t1));//ne pas mettre en argument une tuile vide
  printf("teste tile_edge -> doit renvoyer le nom de la couleur NORD de la tuile t2 : %s\n",color_name(tile_edge(&t2,NORTH)));

  struct deck de;
  deck_init(&de);
  int i = de.size;
  int pair = 0;
  while(i>0)
  {
    printf("[%s",color_name(de.cards[pair].t->tile_colors[0]));
    for (int dir = 1; dir<4;dir ++)
    {
      printf(",%s",color_name(tile_edge(de.cards[pair].t,dir)));
    }
    printf("] : %d fois \n",de.cards[pair].n);
    i -= de.cards[pair].n;
    pair++;
  }
  printf("La taille du deck est de : %d tuiles \n",de.size);

  printf("\n\n\n ****** test pour le fichier queue.c ******\n");
  Queue* q = initQueue();
  printf("teste si le premier element de la file est NULL -> doit envoyer 1 : %d\n",q->firstElement == NULL);
  push(q,&t1);
  push(q,&t2);
  printf("teste top -> doit envoyer 1 : %d\n",top(q)->tile == &t1);
  pop(q);
  printf("teste si t1 a bien ete supprimee -> doit envoyer 1 : %d\n\n",top(q)->tile == &t2);
  popAll(q);


  printf("******test de rand_q******\n");
  printf("file non melangee : ");
  for (int i =0; i<5; i++)
  {
    push(q,&t1);
    printf("t1 ");
  }
  for (int i =0; i<5; i++)
  {
    push(q,&t2);
    printf("t2 ");
  }
  q = rand_q(q);
  printf("\nfile melangee : ");
  while (top(q) != NULL)
  {
    const struct tile *t = top(q)->tile;
    if (t == &t1)
      printf("t1 ");
    if (t == &t2)
      printf("t2 ");
    pop(q);
  }
  


  //int skip = 0;
  //struct deck d;
  //struct board b;
  //struct players players;
  //struct player active_player;
  //struct positions p;
  //const struct tile *t;
  //struct color *c = color_from_name("RED"); 
  //struct tile t1 = {{ c,c,c,c }};
  //struct deck_pair p1 = { &t1,5 };
  
  
  printf("\n\n\n\n");

  struct board b;
  b = board_init(boardSize);
  b.places[1][0]= &t1;
  b.places[5][5]= &t2;
  
  /*
  b = [[ 0 , 0 , 0 , 0 , 0 ],
       [&t1, 0 , 0 , 0 , 0 ],
       [ 0 , 0 , 0 , 0 , 0 ],
       [ 0 , 0 , 0 , 0 , 0 ],
       [ 0 , 0 , 0 , 0 ,&t2] 
  ]
  */

  struct positions pos;
  pos = list_authorized_places(&b,&t2);
  printf("ce resultat doit etre 1 :%d\n",select_position(pos).length);

  place_tile(&b, select_position(pos),&t2);
  printf("ce resultat doit etre 1 :%d\n", b.places[5][4]==&t2);

  
  struct positions p;
  p.i[0]= 1;
  p.i[1]= 2;
  p.j[0]= 1;
  p.j[1]= 3;
  // cela veut dire que les points (1,2),(1,3) sont dans pos
  p.length = 2; // p contient 2 points

  printf("ce restultat doit etre 0 : %d\n", is_empty(&p));



  return EXIT_SUCCESS;
}