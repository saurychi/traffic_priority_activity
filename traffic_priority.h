#ifndef TRAFFIC_PRIORITY_H
#define TRAFFIC_PRIORITY_H
#include <stdio.h>
#include <string.h>

typedef struct{
    char sign[15];
    char lane[15];
} Activity;

typedef struct{
    Activity activity;
    int seconds;
    int priority;
} Lane;

typedef struct{
    Lane arr[8];
    int count;
} PriorityQueue;

void initPQ(PriorityQueue* pq);
Lane createActivity(char* sign, char* lane, int seconds, int priority);
void maxHeapify(PriorityQueue* pq, int i);
void buildmaxHeap(PriorityQueue* pq);
void maxHeapSort(PriorityQueue* pq);
void displayPQ(PriorityQueue pq);
int getTime(PriorityQueue pq, char* start_sign, char* start_lane, char* end_sign, char* end_lane);
void printTraffic(PriorityQueue pq, char* start_sign, char* start_lane, char* end_sign, char* end_lane);

#endif
