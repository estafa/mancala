#include <stdio.h>
#include "functions.h"
#define STARTING
#define NORTH 0
#define SOUTH 1
#define TEMP 0
#define CLEARED 0 
#define INDEX_PILE_POSITION (--pilePosition)
#define FIRST_SOUTHERN_PILE 0;
#define FIRST_NORTHERN_PILE 6
#define LAST_NORTHERN_PILE 11
#define LAST_SOUTHERN_PILE 5 
#define NEXT_PILE (pilePosition + 1)
#define CHECK_NEXT_PILE (current_pile + 1)
#define PILE_IN_SOUTH (pilePosition < LAST_SOUTHERN_PILE)
#define WE_HAVE_PEBBLES (amountOfPebbles != 0)
#define NO_PEBBLES (amountOfPebbles == 0)
#define PEBBLES_IN_PILE gameBoard[current_pile]
#define NORTH_OUT_OF_INDEX 12
#define SOUTH_OUT_OF_INDEX -1

void collect(int gameBoard[], int pilePosition, int currentlyCaptured[]) {
  int amountOfPebbles;
  if (pilePosition == 0) {
    printf("ERROR: INVALID PILE POSITION\n");
    return;
  }
  amountOfPebbles = gameBoard[INDEX_PILE_POSITION]; /* gets the amount of pebbles in the specified current_pile */
  gameBoard[pilePosition] = CLEARED; /* clear the current_pile */
  drop(gameBoard, amountOfPebbles, pilePosition, currentlyCaptured); 
}

/* will drop the pebbles on to the piles */
void drop(int gameBoard[], int amountOfPebbles, int pilePosition, int currentlyCaptured[]) {
  int current_pile = NEXT_PILE;
  int current_side = TEMP; /* 0 = north 1 = south */
  int original_side = TEMP;
  if (PILE_IN_SOUTH) {
    original_side = SOUTH;
  } else {
    original_side = NORTH;
  }

  if (pilePosition == LAST_SOUTHERN_PILE) /* If the passed current_pile is the LAST one of the south */
    current_side = NORTH;                    /* announce where the next side will be. */
  else if (pilePosition == LAST_NORTHERN_PILE) {
    current_side = SOUTH;
    current_pile = FIRST_SOUTHERN_PILE;
  }
  while (WE_HAVE_PEBBLES) { /* distribute pebbles */
    gameBoard[current_pile] += 1;
    amountOfPebbles--;
    if (current_pile == LAST_SOUTHERN_PILE && WE_HAVE_PEBBLES) 
    {
      current_side = NORTH;
      current_pile++;
      continue;
    } else if (current_pile == LAST_NORTHERN_PILE && WE_HAVE_PEBBLES) 
    {
      current_side = SOUTH;
      current_pile = FIRST_SOUTHERN_PILE;
      continue;
    }

    if (NO_PEBBLES && 
        (PEBBLES_IN_PILE == 2 || PEBBLES_IN_PILE == 3) && 
        (original_side != current_side)) 
    {
      capture(gameBoard, current_pile, currentlyCaptured, original_side);
      continue;
    }
    current_pile++;
  }
}

void capture(int gameBoard[], int current_pile, 
             int captured[], int original_side) 
{
  int previous = TEMP;
  int next = TEMP;
  int count = 0, loopCount = 0, i = 0; /* or after the int use count = loopCount = i = 0; */

  if ((current_pile + 1 == NORTH_OUT_OF_INDEX) || (current_pile + 1 == FIRST_NORTHERN_PILE)) 
  {
    previous = gameBoard[current_pile - 1]; /* valid previous value */
    next = SOUTH_OUT_OF_INDEX;
  } 
  else if ((current_pile - 1 == SOUTH_OUT_OF_INDEX) || (current_pile - 1 == LAST_SOUTHERN_PILE)) 
  {
    previous = SOUTH_OUT_OF_INDEX; /* invalid previous value */
    next = gameBoard[current_pile + 1]; /* valid next value */
  }
  else  
  {
    previous = gameBoard[current_pile - 1]; /* valid previous value */
    next = gameBoard[current_pile + 1]; /* valid next value */
  }

  if (current_pile < FIRST_NORTHERN_PILE) {
    i = 0;
    loopCount = 6;
  } else {
    i = 6;
    loopCount = 12;
  }

  if (previous == 0 && next == 0) {
    for (; i < loopCount; i++) {
      count += gameBoard[i];
    }
    count -= gameBoard[current_pile];
    if (count != 0) {
      captured[original_side] += gameBoard[current_pile];
      gameBoard[current_pile] = 0;
    }
  } 
  else if (previous == -1 &&
             next != 0) { /* at first element for either north or south */
    captured[original_side] += gameBoard[current_pile];
    gameBoard[current_pile] = 0;
  } else if (previous != 0 &&
             next == -1) { /* at last element for either north or south*/
    if (callMeV2(gameBoard, current_pile, loopCount) >= 0) {
      captured[original_side] += callMeV2(gameBoard, current_pile, loopCount);
    }
  } else if (previous != 0 && next != 0) {
    captured[original_side] += callMe(gameBoard, current_pile, loopCount);
  } else if (previous != 0 && next == 0) {
    for (; i < loopCount; i++) {
      count += gameBoard[i];
    }
    count -= gameBoard[current_pile];

    if (count != 0) {
      captured[original_side] += callMe(gameBoard, current_pile, loopCount);
    } else {
      printf("there was nothing for me to do");
    }
  } else if (previous == 0 && next != 0) {
    captured[original_side] += gameBoard[current_pile];
    gameBoard[current_pile] = 0;
  }
}

int callMe(int gameBoard[], int current_pile, int loopCount) {
  int count = 0;
  int previous = current_pile - 1;
  if (previous < (loopCount - 6)) {
    count += gameBoard[current_pile];
    gameBoard[current_pile] = 0;
    return count;
  }
  if ((gameBoard[previous] == 3) || (gameBoard[previous] == 2)) {
    count += callMe(gameBoard, previous, loopCount);
    count += gameBoard[current_pile];
    gameBoard[current_pile] = 0;
  } else {
    count += gameBoard[current_pile];
    gameBoard[current_pile] = 0;
  }
  return count;
}

int callMeV2(int gameBoard[], int current_pile, int loopCount) {
  int count = 0;
  int previous = current_pile - 1;
  if (previous < (loopCount - 6)) {
    return -100;
  }
  if ((gameBoard[previous] == 3) || (gameBoard[previous] == 2)) {
    count += callMeV2(gameBoard, previous, loopCount);
    if (count < 0) {
      return count;
    } else {
      count += gameBoard[current_pile];
      gameBoard[current_pile] = 0;
    }
  }

  return count;
}

void printFinalResult (int piles[], int captured[]) {
  printf("\n        Pits and Pebbles       \n");
  printf("        ----------------       \n\n");
  printf("             North               \n\n");
  printf("  12   11   10    9    8    7\n");
  printf("+----+----+----+----+----+----+\n|");
  printf(" %2d | %2d | %2d | %2d | %2d | %2d ", piles[11], piles[10], piles[9],
         piles[8], piles[7], piles[6]);
  printf("|    North %2d\n+----+----+----+----+----+----+\n|", captured[0]);
  printf(" %2d | %2d | %2d | %2d | %2d | %2d ", piles[0], piles[1], piles[2],
         piles[3], piles[4], piles[5]);
  printf("|    South %2d\n+----+----+----+----+----+----+\n", captured[1]);
  printf("   1    2    3    4    5    6\n");
  printf("\n             South               \n\n");
} /* prints to screen the reuslt */
