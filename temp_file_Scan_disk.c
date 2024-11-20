#include <stdio.h>
#include <stdlib.h>

int head = 53, max = 12;

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

void Scan_Algorithm(int arr[], int max) {
    int arr1[100], arr2[100];  // Arrays to separate Disks
    int j = 0, k = 0;
    
    // Split Disks into two arrays: one with values less than the head, and one greater than the head
    for (int i = 0; i < max; i++) {
        if (arr[i] < head) {
            arr1[j++] = arr[i];  // Add to arr1 (values less than head)
        } else {
            arr2[k++] = arr[i];  // Add to arr2 (values greater than or equal to head)
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
}

int main() {
    int requests[] = {100, 85, 45, 55, 120, 20, 70, 90, 115, 65, 130, 145};
    int size = sizeof(requests) / sizeof(requests[0]);
    
    Scan_Algorithm(requests, size);

    return 0;
}
