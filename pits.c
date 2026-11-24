#include <stdio.h>
#include "functions.h"
/* collect, drop, capture */
/* taken = {0, 0} */
/* {north, south} */
/*   2   |   1    */
#define SOUTH 1
#define NORTH 2

/* pass actual position of pile not the index */ 
int main(int argc, char* argv[]) {
  int gameBoard [12];
  char stringHolder[400];
  int count = 0;

  printf("argc = %d\n", argc);
  FILE *fileptr;
  if (argc > 1) 
    fileptr = fopen(argv[1],"r"); 
  else
    return 1;

  if (fileptr == NULL) {
    printf("Not able to open the file.");
    return 1;
  }
  else {
    while (fgets(stringHolder, sizeof(stringHolder), fileptr) != NULL) {
      if (count == 0) {
        count++;
        continue;
      }
      printf("%s", stringHolder);
      // knowing that north and south will only have 6 or index 5 we can just
      // look for them using indices 11.

      int p = 0;
      if (count == 1)
        p = 0;
      else if (count == 2)
        p = 11;

      if (count == 1 || count == 2) {
        // skip "spaces" in the line
        for (int i = 0; i < 11; i++) { 
          if (stringHolder[i] >= '0' && stringHolder[i] <= '9') {  
            if (count == SOUTH) {
              int num = stringHolder[i] - '0';
              printf("p: %d\n", p);
              gameBoard[p] = num;
              p++;
            } else {
              int num = stringHolder[i] - '0';
              printf("p: %d\n", p);
              gameBoard[p] = num;
              p--;
            }
            printf("%d: %c\n", i+1, stringHolder[i]);
          } else 
            continue;
        }

      }
      count++;

    }

    fclose(fileptr);
  }
  


  int captured[] = {23, 14};
  // int gameBoard[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
  // int gameBoard[] = {0, 1, 2, 0, 0, 4,  /* SOUTH PILES */
  //                    4, 4, 4, 2, 1, 4}; /* NORTH PILES */
  // collect(gameBoard, 6, captured); /* to make a new move collect() has to be called again */
  // collect(gameBoard, 9, captured);
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
