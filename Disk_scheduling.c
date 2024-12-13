#include <stdio.h>
#include <stdlib.h>

int queue[100], head, sum[100], max;

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

// Sorting functions
void Sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i) {
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
}

void Dsort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] > arr[max_idx])
                max_idx = j;
        }
        if (max_idx != i) {
            int temp = arr[max_idx];
            arr[max_idx] = arr[i];
            arr[i] = temp;
        }
    }
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
    int flag[100] = {0};  // Keeps track of whether a request has been processed
    int distance[100];
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

// SCAN Disk Scheduling Algorithm
void SCAN() {
    int arr1[100], arr2[100];  // Arrays to separate Disks
    int j = 0, k = 0;

    // Split Disks into two arrays: one with values less than the head, and one greater than the head
    for (int i = 0; i < max; i++) {
        if (queue[i] < head) {
            arr1[j++] = queue[i];  // Add to arr1 (values less than head)
        } else {
            arr2[k++] = queue[i];  // Add to arr2 (values greater than or equal to head)
        }
    }

    // Sort arr1 in descending order, arr2 in ascending order
    Dsort(arr1, j);  // Sort arr1 in descending order
    Sort(arr2, k);   // Sort arr2 in ascending order

    // Merge the two sorted arrays: arr1 (descending) + head + arr2 (ascending)
    int merged[100];
    int index = 0;

    // Copy arr1 (descending) into merged array
    for (int i = 0; i < j; i++) {
        merged[index++] = arr1[i];
    }

    // Add the head to the merged array
    merged[index++] = head;

    // Copy arr2 (ascending) into merged array
    for (int i = 0; i < k; i++) {
        merged[index++] = arr2[i];
    }

    // Now calculate the seek times
    printf("--SCAN--\n");
    int sum[100];
    sum[0] = abs(head - merged[0]);
    printf("The seek from %d to %d is %d\n", head, merged[0], sum[0]);

    int total_seek = sum[0];
    for (int i = 1; i < max; i++) {
        sum[i] = abs(merged[i] - merged[i - 1]);
        printf("The seek from %d to %d is %d\n", merged[i - 1], merged[i], sum[i]);
        total_seek += sum[i];
    }

    printf("The total seek time is: %d\n", total_seek);
    printf("----\n");
}

int main() {
    int choice;
    printf("Enter the maximum number of disks: ");
    if (scanf("%d", &max) != 1 || max <= 0 || max > 100) {
        printf("Invalid input. Please enter a positive integer between 1 and 100.\n");
        return 1;
    }

    printf("Enter the disk values: ");
    for (int i = 0; i < max; i++) {
        if (scanf("%d", &queue[i]) != 1) {
            printf("Invalid input. Please enter integer values.\n");
            return 1;
        }
    }

    printf("Enter the head value: ");
    if (scanf("%d", &head) != 1) {
        printf("Invalid input. Please enter an integer value.\n");
        return 1;
    }

    printf("1. FCFS\n2. SSTF\n3. SCAN\n4. Exit\n");

    while (1) {
        printf("Enter the choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid choice.\n");
            return 1;
        }
        switch (choice) {
            case 1:
                FCFS();
                break;
            case 2:
                SSTF();
                break;
            case 3:
                SCAN();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid operation.\n");
        }
    }

    return 0;
}
