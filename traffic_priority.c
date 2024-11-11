#include "traffic_priority.h"
#include <stdio.h>
#include <string.h>

void initPQ(PriorityQueue* pq){
    pq->count = 0;
}

Lane createActivity(char* sign, char* lane, int seconds, int priority){
    Lane l;
    Activity a;
    strcpy(a.sign, sign);
    strcpy(a.lane, lane);
    l.activity = a;
    l.seconds = seconds;
    l.priority = priority;

    return l;
}

void maxHeapify(PriorityQueue* pq, int i){
    int left = (i*2)+1;
    int right = (i*2)+2;
    int largest = i;

    if(left > pq->count && right > pq->count){
        return;
    }

    if(left < pq->count && pq->arr[left].priority > pq->arr[largest].priority){
        largest = left;
    }

    if(right < pq->count && pq->arr[right].priority > pq->arr[largest].priority){
        largest = right;
    }

    if(largest != i){
        Lane temp = pq->arr[i];
        pq->arr[i] = pq->arr[largest];
        pq->arr[largest] = temp;
        maxHeapify(pq, largest);
    }
}

void buildmaxHeap(PriorityQueue* pq){
    for(int i = (pq->count/2)-1; i >= 0; i--){
        maxHeapify(pq, i);
    }
}

void maxHeapSort(PriorityQueue* pq){
    int og_count = pq->count;
    Lane temp;

    while(pq->count != 0){
        temp = pq->arr[0];
        pq->arr[0] = pq->arr[pq->count-1];
        pq->arr[pq->count-1] = temp;
        pq->count--;
        maxHeapify(pq, 0);
    }

    pq->count = og_count;
}

void displayPQ(PriorityQueue pq){
    for(int i = 0; i < pq.count; i++){
        printf("\n%d. %-10s %-10s %d seconds", pq.arr[i].priority, pq.arr[i].activity.sign, pq.arr[i].activity.lane, pq.arr[i].seconds);
    }
}

int getTime(PriorityQueue pq, char* start_sign, char* start_lane, char* end_sign, char* end_lane){
    int startInd, sum = 0;
    for(int i = 0; i < pq.count; i++){
        if(strcmp(start_sign, pq.arr[i].activity.sign) == 0 && strcmp(start_lane, pq.arr[i].activity.lane) == 0){
            startInd = i;
            break;
        }
    }
    int count = 1;
    for(int i = startInd; count < pq.count; i = (i+1)%pq.count){
        if(strcmp(end_sign, pq.arr[i].activity.sign) == 0 && strcmp(end_lane, pq.arr[i].activity.lane) == 0){
            break;
        }
        sum += pq.arr[i].seconds;
        // printf("\n%d", i);
        count++;
    }

    return sum;
}

void printTraffic(PriorityQueue pq, char* start_sign, char* start_lane, char* end_sign, char* end_lane){
    FILE *pf = fopen("traffic.dat", "w");

    if(pf == NULL){
        perror("\nFile not created");
        return;
    }

    fprintf(pf, "Priority    Sign       Lane       Seconds\n");
    for(int i = 0; i < pq.count; i++){
        fprintf(pf, "Priority %d: %-10s %-10s %d seconds\n", i, pq.arr[i].activity.sign, pq.arr[i].activity.lane, pq.arr[i].seconds);
    }

    int startInd, sum = 0;
    for(int i = 0; i < pq.count; i++){
        if(strcmp(start_sign, pq.arr[i].activity.sign) == 0 && strcmp(start_lane, pq.arr[i].activity.lane) == 0){
            startInd = i;
            break;
        }
    }
    int count = 1;
    for(int i = startInd; count < pq.count; i = (i+1)%pq.count){
        if(strcmp(end_sign, pq.arr[i].activity.sign) == 0 && strcmp(end_lane, pq.arr[i].activity.lane) == 0){
            break;
        }
        sum += pq.arr[i].seconds;
        // printf("\n%d", i);
        count++;
    }

    fprintf(pf, "\nTime to take from 'straight main' to 'pedestrian main' is: %d", sum);

    fclose(pf);
}
