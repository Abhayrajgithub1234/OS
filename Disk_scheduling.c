#include <stdio.h>
#include <stdlib.h>

int queue[10], head, sum[10];
int max;

// Function to find the index of the smallest value in an array
int smallest(int array[], int flag[]) {
    int index = -1, smallest = 9999;
    for (int i = 0; i < max; i++) {
        if (flag[i] == 0 && array[i] < smallest) {
            smallest = array[i];
            index = i;
        }
    }
    return index;
}

// FCFS Disk Scheduling Algorithm
void FCFS() {
    printf("--FCFS--\n");
    sum[0] = abs(head - queue[0]);
    printf("The seek from %d to %d is %d\n", head, queue[0], sum[0]);

    int total_seek = sum[0];
    for (int i = 1; i < max; i++) {
        sum[i] = abs(queue[i] - queue[i - 1]);
        printf("The seek from %d to %d is %d\n", queue[i - 1], queue[i], sum[i]);
        total_seek += sum[i];
    }

    printf("The total seek time is: %d\n", total_seek);
    printf("----\n");
}

// SSTF Disk Scheduling Algorithm
void SSTF() {
    int flag[10] = {0};  // Keeps track of whether a request has been processed
    int distance[10];
    int total_seek = 0;

    printf("--SSTF--\n");
    int current_position = head;

    for (int i = 0; i < max; i++) {
        // Calculate distances from the current head position
        for (int j = 0; j < max; j++) {
            if (flag[j] == 0) {  // Only consider unprocessed requests
                distance[j] = abs(current_position - queue[j]);
            } else {
                distance[j] = 9999;  // Mark processed requests with a high value
            }
        }

        int index = smallest(distance, flag);  // Find the nearest request
        flag[index] = 1;  // Mark this request as processed
        sum[i] = abs(current_position - queue[index]);
        printf("The seek from %d to %d is %d\n", current_position, queue[index], sum[i]);
        total_seek += sum[i];
        current_position = queue[index];
    }

    printf("The total seek time is: %d\n", total_seek);
    printf("----\n");
}

int main() {
    int choice;
    printf("Enter the maximum number of disks: ");
    scanf("%d", &max);

    if (max <= 0 || max > 10) {
        printf("Invalid number of disks.\n");
        return 1;
    }

    printf("Enter the disk values: ");
    for (int i = 0; i < max; i++) {
        scanf("%d", &queue[i]);
    }

    printf("Enter the head value: ");
    scanf("%d", &head);

    printf("1. FCFS\n2. SSTF\n3. Exit\n");

    while (1) {
        printf("Enter the choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                FCFS();
                break;
            case 2:
                SSTF();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid operation.\n");
        }
    }

    return 0;
}
