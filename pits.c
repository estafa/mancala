#include <stdio.h>
/* collect, drop, capture */
/* taken = {0, 0} */
/* {north, south} */
/*   0   |   1    */

void printToScreen(int piles[], int captured[]) {
    printf("\n        Pits and Pebbles       \n");
    printf("        ----------------       \n\n");
    printf("             North               \n\n");
    printf("  12   11   10    9    8    7\n");
    printf("+----+----+----+----+----+----+\n|");
    printf(" %2d | %2d | %2d | %2d | %2d | %2d ", piles[11], piles[10], piles[9], piles[8], piles[7], piles[6]);
    printf("|    North %2d\n+----+----+----+----+----+----+\n|", captured[0]);
    printf(" %2d | %2d | %2d | %2d | %2d | %2d ",  piles[0], piles[1], piles[2], piles[3], piles[4], piles[5]);
    printf("|    South %2d\n+----+----+----+----+----+----+\n", captured[1]);
    printf("   1    2    3    4    5    6\n");
    printf("\n             South               \n\n");

}

int callMe(int piles[], int pile, int loopCount){
    int count = 0;
    int previous = pile - 1;
    if (previous < (loopCount - 6 )) {
        count += piles[pile];
        piles[pile] = 0;
        return count;
    }
    if ((piles[previous] == 3) || (piles[previous] == 2)){
        count += callMe(piles, previous, loopCount);
        count += piles[pile];
        piles[pile] = 0;
    } else {
        count += piles[pile];
        piles[pile] = 0;
    }
    return count;
}

int callMeV2(int piles[], int pile, int loopCount){
    int count = 0;
    int previous = pile - 1;
    if (previous < (loopCount - 6 )) {
        return -100;

    }
    if ((piles[previous] == 3) || (piles[previous] == 2)){
        count += callMeV2(piles, previous, loopCount);
        if (count < 0) {
            return count;
        } else {
            count += piles[pile];
            piles[pile] = 0;
        }
    } 

    return count;
}

void capture(int piles[], int current_pile, int captured[], int original_side) {
    int previous = 0; 
    int next = 0;
    int count = 0;
    int loopCount = 0;
    int i = 0;

    if ((current_pile + 1 == 12) || (current_pile + 1 == 6)) {
       previous = piles[current_pile - 1];
       next = -1;
    } 
    else if ((current_pile - 1 == -1) || (current_pile - 1 == 5)) {
       previous = -1;
       next = piles[current_pile + 1];
    } 
    else {
       previous = piles[current_pile - 1];
       next = piles[current_pile + 1];
    }

    if (current_pile < 6) {
        i = 0;
        loopCount = 6;
    } else {
        i = 6;
        loopCount = 12;
    }

    if (previous == 0 && next == 0) {
        for (; i < loopCount; i++) {
            count += piles[i];
        }
        count -= piles[current_pile];
        if(count != 0) {
            captured[original_side] += piles[current_pile];
            piles[current_pile] = 0;
        } else {
        }
    } 
    else if ( previous == -1 && next != 0) {  /* at first element for either north or south */
        captured[original_side] += piles[current_pile];
        piles[current_pile] = 0;
    } 
    else if ( previous != 0 && next == -1) { /* at last element for either north or south*/
        if (callMeV2(piles, current_pile, loopCount) >= 0) { 
            captured[original_side] += callMeV2(piles, current_pile, loopCount);
        }

    } 
    else if (previous != 0 && next != 0) {
        captured[original_side] += callMe(piles, current_pile, loopCount); 
    } 
    else if (previous != 0 && next == 0) {
        for (; i < loopCount; i++) {
            count += piles[i];
        }
        count -= piles[current_pile];

        if(count != 0) {
            captured[original_side] += callMe(piles, current_pile, loopCount); 
        } else {
            printf("there was nothing for me to do");
        }
    } 
    else if (previous == 0 && next != 0) {
        captured[original_side] += piles[current_pile];
        piles[current_pile] = 0;
    }
}


void drop(int piles[], int amount, int position, int captured[]) {
    int pile = position + 1; 
    int current_side = 0;  /* 0 = north 1 = south */
    int original_side = 0;
    if (position < 6) {
        current_side = 1;
    }
    original_side = current_side;

    if (position == 5) 
        current_side = 0;
    else if (position == 11) {
        current_side = 1;
        pile = 0;
    } 
    while(amount != 0) {
        piles[pile] += 1; 
        amount--;
        if (pile == 5 && amount != 0) { 
            current_side = 0;
            pile++;
            continue;
        } else if (pile == 11 && amount != 0) {
            current_side = 1;
            pile = 0;
            continue;
        }

        if ((amount == 0 ) && (piles[pile] == 2 || piles[pile] == 3) && (original_side != current_side)){
            capture(piles, pile, captured, original_side);
            continue;
        }
        pile++;

    }
}


void collect(int piles[], int position, int captured[]) { 
    int value = piles[position];
    piles[position] = 0;
    drop(piles, value, position, captured);
}




int main() {
    int captured[] = {23, 14};
    /* int newGame[] = { 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4}; */
    int newGame[] = { 1, 0, 0, 3, 2, 1,
       0, 1, 1, 1, 0, 1};
    collect(newGame, 11, captured);
    /*collect(newGame, 11, captured);
    collect(newGame, 5, captured);
    collect(newGame, 9, captured);
    collect(newGame, 11, captured);
    collect(newGame, 2, captured);
    collect(newGame, 3, captured);
    collect(newGame, 10, captured);
    collect(newGame, 5, captured); */
    printToScreen(newGame, captured);
    return 0;
}

/* add one to each array */
