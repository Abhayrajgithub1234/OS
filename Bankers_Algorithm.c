#include <stdio.h>
#include <stdbool.h>

int pCount, rCount, alloc[10][10], maxReq[10][10], need[10][10], avail[10];
int safeSeq[10], seqIdx = 0; // To store safe sequence
bool finished[10] = {false}; // To track process completion

// Function to calculate Need Matrix
void calcNeed() {
    for (int i = 0; i < pCount; i++) {
        for (int j = 0; j < rCount; j++) {
            need[i][j] = maxReq[i][j] - alloc[i][j];
        }
    }
}

// Banker's Algorithm to find Safe Sequence
void bankersAlgo() {
    int finishedStatus[10] = {0}; // To track finished processes
    int resIdx = 0;

    for (int k = 0; k < pCount; k++) {
        for (int i = 0; i < pCount; i++) {
            if (finishedStatus[i] == 0) {
                int canExec = 0;
                for (int j = 0; j < rCount; j++) {
                    if (need[i][j] > avail[j]) {
                        canExec = 1;
                        break;
                    }
                }

                // If the process can be executed
                if (canExec == 0) {
                    safeSeq[seqIdx++] = i;
                    for (resIdx = 0; resIdx < rCount; resIdx++) {
                        avail[resIdx] += alloc[i][resIdx]; // Releasing resources
                    }
                    finishedStatus[i] = 1; // Marking process as finished
                }
            }
        }
    }

    // Checking if all processes are finished
    int allFinished = 1;
    for (int i = 0; i < pCount; i++) {
        if (finishedStatus[i] == 0) {
            allFinished = 0;
            printf("The system is not in a safe state.\n");
            break;
        }
    }

    if (allFinished == 1) {
        printf("Following is the SAFE Sequence:\n");
        for (int i = 0; i < pCount - 1; i++)
            printf(" P%d ->", safeSeq[i]);
        printf(" P%d\n", safeSeq[pCount - 1]);
    }
}

int main() {
    // Getting the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &pCount);

    // Getting the number of resources
    printf("Enter the number of resources: ");
    scanf("%d", &rCount);

    // Getting the allocation of each process
    printf("Enter the allocation for each process\n");
    for (int i = 0; i < pCount; i++) {
        for (int j = 0; j < rCount; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Getting the maximum requirement for each process
    printf("Enter the maximum requirement for each process\n");
    for (int i = 0; i < pCount; i++) {
        for (int j = 0; j < rCount; j++) {
            scanf("%d", &maxReq[i][j]);
        }
    }

    // Getting the availability of each resource
    printf("Enter the availability of each type of resource\n");
    for (int i = 0; i < rCount; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculating the Need matrix
    calcNeed();

    // Printing the Need matrix
    printf("Need matrix is:\n");
    for (int i = 0; i < pCount; i++) {
        for (int j = 0; j < rCount; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Running the Banker's Algorithm to check for safe sequence
    bankersAlgo();

    return 0;
}
