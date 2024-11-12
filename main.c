#include "traffic_priority.c"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(){
    PriorityQueue pq;

    pq.arr[0] = createActivity("straight", "main", 50, 1);
    pq.arr[1] = createActivity("left", "diversion", 20, 4);
    pq.arr[2] = createActivity("right", "main", 25, 5);
    pq.arr[3] = createActivity("pedestrian", "diversion", 20, 8);
    pq.arr[4] = createActivity("straight", "diversion", 30, 2);
    pq.arr[5] = createActivity("left", "main", 25, 3);
    pq.arr[6] = createActivity("right", "diversion", 20, 6);
    pq.arr[7] = createActivity("pedestrian", "main", 15, 7);

    pq.count = 8;

    buildmaxHeap(&pq);
    // displayPQ(pq);

    /*

       8
     5   7
    4 1 6 3
   2

    */
    maxHeapSort(&pq);
    displayPQ(pq);

    int result = getTime(pq, "straight", "main", "pedestrian", "main");
    printf("\n\nTime to take from 'straight main' to 'pedestrian main' is: %d\n", result);

    char first_sign[50], first_lane[50], last_sign[50], last_lane[50];
    printf("\nEnter first sign: ");
    scanf(" %s", first_sign);
    printf("Enter first lane: ");
    scanf(" %s", first_lane);
    printf("Enter last sign: ");
    scanf(" %s", last_sign);
    printf("Enter last lane: ");
    scanf(" %s", last_lane);

    activityOne(pq, first_sign, first_lane, last_sign, last_lane);

    char choice[4];
    printf("\nProceed to Activity 2? (yes/no): ");
    scanf(" %s", choice);

    for(int i = 0; i < strlen(choice) && choice[i] != '\n' && choice[i] != '\0' && isalpha(choice[i]) && isupper(choice[i]); i++){
        choice[i] += 32;
    }

    // printf("\n\nChoice: %s", choice);

    if(strcmp(choice, "yes") == 0){
        activityTwo(pq);
    } else if(strcmp(choice, "no") == 0){
        return 0;
    }

}
