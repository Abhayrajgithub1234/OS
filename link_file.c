#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int min = 0;
int max = 99;

// Generate a random number in the range [min, max].
int generateRandoms() {
    return rand() % (max - min + 1) + min;
}

// Print memory allocation for a file.
void allocation(int num, int memory[], int start) {
    int count = 0;
    printf("file%d.txt\tstart: %d\t", num, start);
    for (int i = 0; i < 100; i++) {
        if (memory[i] == num) {
            printf("%d -> ", i);
            count++;
        }
    }
    printf("NULL\n");
    printf("Count: %d\n", count);
}

// Allocate memory for a file with exactly 10 nodes.
int allocateMemory(int fileNum, int memory[], int size) {
    int start = -1; // Initialize start address.
    int allocated = 0;

    while (allocated < size) { // Allocate exactly `size` nodes.
        int value = generateRandoms();
        if (memory[value] == 0) { // Only allocate if the location is free.
            memory[value] = fileNum;
            if (start == -1) {
                start = value; // Set the start address for the file.
            }
            allocated++;
        }
    }
    return start;
}

int main() {
    srand(time(NULL)); // Seed random number generator.

    int memory[100] = {0}; // Initialize memory.
    int choice, start1, start2;

    // Allocate memory for file1.txt and file2.txt.
    start1 = allocateMemory(1, memory, 10);
    start2 = allocateMemory(2, memory, 10);

    printf("1. File1.txt\n2. File2.txt\n3. Exit\n");

    // User interaction loop.
    while (1) {
        printf("Enter the choice of file data allocations to be viewed: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("The linked file allocation of file1.txt is:\n");
                allocation(1, memory, start1);
                break;
            case 2:
                printf("The linked file allocation of file2.txt is:\n");
                allocation(2, memory, start2);
                break;
            case 3:
                return 0; // Exit the program.
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
