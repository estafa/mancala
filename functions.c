#include <stdio.h>
#include "functions.h"
#define NORTH 0
#define SOUTH 1
#define TEMP 0
#define CLEARED 0 
#define INDEX_PILE_POSITION (--pilePosition)
#define FIRST_SOUTHERN_INDEX 0;
#define FIRST_NORTHERN_PILE_INDEX 6
#define LAST_NORTHERN_PILE 11
#define LAST_SOUTHERN_PILE 5 
#define NEXT_PILE (pilePosition + 1)
#define CHECK_NEXT_PILE (current_pile_index + 1)
#define PILE_IN_SOUTH (pilePosition <= LAST_SOUTHERN_PILE)
#define WE_HAVE_PEBBLES (amountOfPebbles != 0)
#define NO_PEBBLES (amountOfPebbles == 0)
#define PEBBLES_IN_PILE (gameBoard[current_pile_index])
#define NORTH_OUT_OF_INDEX 12
#define SOUTH_OUT_OF_INDEX -1
#define NEXT_INDEX (current_pile_index + 1)
#define PREVIOUS_INDEX (current_pile_index - 1)
#define CURRENT_IS_NOT_NORTHERN_PILE (current_pile_index < FIRST_NORTHERN_PILE_INDEX)


void collect(int gameBoard[], int pilePosition, int currentlyCaptured[]) {
  int amountOfPebbles;

  if (pilePosition == 0) {
    printf("ERROR: INVALID PILE POSITION\n");
    return;
  }
  amountOfPebbles = gameBoard[INDEX_PILE_POSITION]; /* gets the amount of pebbles in the specified current_pile_index */
  gameBoard[pilePosition] = CLEARED; /* clear the current_pile_index */
  drop(gameBoard, amountOfPebbles, 
      pilePosition, currentlyCaptured); 
}

/* will drop the pebbles on to the piles */
void drop(int gameBoard[], int amountOfPebbles, 
         int pilePosition, int currentlyCaptured[]) 
{
  int current_pile_index = NEXT_PILE;
  int current_side = TEMP; /* 0 = north 1 = south */
  int original_side = TEMP;

  if (PILE_IN_SOUTH) {  /* checks where the move started */ 
    original_side = SOUTH;
    current_side = SOUTH;
  } else {
    original_side = NORTH;
    current_side = NORTH;
  }
  
  if (pilePosition == LAST_SOUTHERN_PILE) /* If the passed current_pile_index is the LAST one of the south */
    current_side = NORTH;                    /* announce where the next_value side will be. */
  else if (pilePosition == LAST_NORTHERN_PILE) {
    current_side = SOUTH;
    current_pile_index = FIRST_SOUTHERN_INDEX;
  }

  while (WE_HAVE_PEBBLES) { /* distribute pebbles */
    gameBoard[current_pile_index] += 1; /* adding one pebble to the current pile */
    amountOfPebbles--;

    if (current_pile_index == LAST_SOUTHERN_PILE && WE_HAVE_PEBBLES) {
      current_side = NORTH;
      current_pile_index++;
      printf("BYE\n");
      continue;
    } else if (current_pile_index == LAST_NORTHERN_PILE && WE_HAVE_PEBBLES) {
      current_side = SOUTH;
      printf("HELLOOOOO\n");
      current_pile_index = FIRST_SOUTHERN_INDEX;
      continue;
    }

    printf("%d\n", original_side);

    if (NO_PEBBLES && 
       (PEBBLES_IN_PILE == 2 || PEBBLES_IN_PILE == 3) && 
       (original_side != current_side)) {
      printf("%d HLEO\n ", current_side);
      capture(gameBoard, current_pile_index, 
              currentlyCaptured, original_side);
      continue;
    }
    current_pile_index++; /* move to the next pile */
  }
}


void capture(int gameBoard[], int current_pile_index, 
             int captured[], int original_side) 
{
  int previous_value = TEMP;
  int next_value = TEMP;
  int count = 0, loopCount = 0, i = 0; /* or after the int use count = loopCount = i = 0; */

  /* it is checking if something is ahead to see make sure it is ok to collect the previous pile */
  /* logic to determine whether we should check the next_value pile / previous_value pile */
  if ((NEXT_INDEX == NORTH_OUT_OF_INDEX) || 
      (NEXT_INDEX == FIRST_NORTHERN_PILE_INDEX)) {
    previous_value = gameBoard[current_pile_index - 1]; /* valid previous_value value */
    next_value = SOUTH_OUT_OF_INDEX;
  } else if ((PREVIOUS_INDEX == SOUTH_OUT_OF_INDEX) || 
             (PREVIOUS_INDEX == LAST_SOUTHERN_PILE)) {
    previous_value = SOUTH_OUT_OF_INDEX; /* invalid previous_value value */
    next_value = gameBoard[NEXT_INDEX]; /* valid next_value value */
  }
  else {
    previous_value = gameBoard[PREVIOUS_INDEX]; /* valid previous_value value */
    next_value = gameBoard[NEXT_INDEX]; /* valid next_value value */
  }

  if (CURRENT_IS_NOT_NORTHERN_PILE) { /* Used for the first if condition */
    i = 0;                            /* to make sure that there are more pebbles */
    loopCount = 6;                    /* left for the other side to make a move next round.*/
  } else {
    i = 6;
    loopCount = 12;
  }

  if (previous_value == 0 && next_value == 0) {  /* Checking making sure that      */
    for (; i < loopCount; i++) {                 /* there is something to collect. */
      printf("I'm here"); 
      count += gameBoard[i]; 
    } 
    count -= gameBoard[current_pile_index];
    if (count != 0) {
      captured[original_side] += gameBoard[current_pile_index];
      gameBoard[current_pile_index] = 0;
    }
  } else if (previous_value == SOUTH_OUT_OF_INDEX && next_value != 0) {    /* at first element for either north or south */
    captured[original_side] += gameBoard[current_pile_index];
    gameBoard[current_pile_index] = 0;
  } else if (previous_value != 0 && next_value == SOUTH_OUT_OF_INDEX) {
   /* at last element for either north or south*/
    if (callMeV2(gameBoard, current_pile_index, loopCount) >= 0) {
      captured[original_side] += callMeV2(gameBoard, current_pile_index, loopCount);
    }
  } else if (previous_value != 0 && next_value != 0) {
    captured[original_side] += callMe(gameBoard, current_pile_index, loopCount);
  } else if (previous_value != 0 && next_value == 0) {
    for (; i < loopCount; i++) {
      count += gameBoard[i];
    }
    count -= gameBoard[current_pile_index];

    if (count != 0) {
      captured[original_side] += callMe(gameBoard, current_pile_index, loopCount);
    } else {
      printf("there was nothing for me to do");
    }
  } else if (previous_value == 0 && next_value != 0) {
    captured[original_side] += gameBoard[current_pile_index];
    gameBoard[current_pile_index] = 0;
  }
}

int callMe(int gameBoard[], int current_pile_index, int loopCount) {
  int count = 0;
  int previous_value = current_pile_index - 1;
  if (previous_value < (loopCount - 6)) {
    count += gameBoard[current_pile_index];
    gameBoard[current_pile_index] = 0;
    return count;
  }
  if ((gameBoard[previous_value] == 3) || (gameBoard[previous_value] == 2)) {
    count += callMe(gameBoard, previous_value, loopCount);
    count += gameBoard[current_pile_index];
    gameBoard[current_pile_index] = 0;
  } else {
    count += gameBoard[current_pile_index];
    gameBoard[current_pile_index] = 0;
  }
  return count;
}

int callMeV2(int gameBoard[], int current_pile_index, int loopCount) {
  int count = 0;
  int previous_value = current_pile_index - 1;
  if (previous_value < (loopCount - 6)) {
    return -100;
  }
  if ((gameBoard[previous_value] == 3) || (gameBoard[previous_value] == 2)) {
    count += callMeV2(gameBoard, previous_value, loopCount);
    if (count < 0) {
      return count;
    } else {
      count += gameBoard[current_pile_index];
      gameBoard[current_pile_index] = 0;
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
