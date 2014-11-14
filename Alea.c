/*--------------------------------------------------------------*/
/* Reussites. Michel Bonin, Catherine Parent, octobre 2005, 
   d'apres les algorithmes de Pierre-Claude Scholl              */
/*--------------------------------------------------------------*/

/* Générateur aléatoire */

#include <stdlib.h>
#include <time.h>

void InitAlea()
{
  int g;
  time_t t;

  g = (unsigned int) time(&t);
  srand(g);
}

int UnEntier(int n)
{
  /* tirage aléatoire d'un entier entre 1 et n */
  
  return rand()%n + 1;
}


