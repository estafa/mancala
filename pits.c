#include <stdio.h>
#include "functions.h"
/* collect, drop, capture */
/* taken = {0, 0} */
/* {north, south} */
/*   0   |   1    */

/* pass actual position of pile not the index */ 
int main() {
  int captured[] = {23, 14};
  /* int gameBoard[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}; */
  int gameBoard[] = {0, 1, 2, 0, 0, 4,  /* SOUTH PILES */
                     4, 4, 4, 2, 1, 4}; /* NORTH PILES */
  collect(gameBoard, 6, captured); /* to make a new move collect() has to be called again */
  collect(gameBoard, 9, captured);
  /*
    collect(newGame, 5, captured);
    collect(newGame, 9, captured);
    collect(newGame, 11, captured);
    collect(newGame, 2, captured);
    collect(newGame, 3, captured);
    collect(newGame, 10, captured);
    collect(newGame, 5, captured); */
  printFinalResult(gameBoard, captured);
  return 0;
}

/* add one to each array */
