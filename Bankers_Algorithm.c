#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void inputMatrices(int n, int m, int alloc[][MAX_RESOURCES], int max[][MAX_RESOURCES], int avail[]) {
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &avail[i]);
}

void calculateNeed(int n, int m, int need[][MAX_RESOURCES], int max[][MAX_RESOURCES], int alloc[][MAX_RESOURCES]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

bool isSafeState(int n, int m, int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES], int avail[], int safeSequence[]) {
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

int main() {
    int n, m;
    int alloc[MAX_PROCESSES][MAX_RESOURCES], max[MAX_PROCESSES][MAX_RESOURCES];
    int avail[MAX_RESOURCES], need[MAX_PROCESSES][MAX_RESOURCES];
    int safeSequence[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    inputMatrices(n, m, alloc, max, avail);
    calculateNeed(n, m, need, max, alloc);

    if (isSafeState(n, m, alloc, need, avail, safeSequence)) {
        printf("System is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < n; i++) {
            printf("P%d", safeSequence[i]);
            if (i != n - 1)
                printf(" -> ");
        }
        printf("\n");
    } else {
        printf("System is not in a safe state!\n");
    }

    return 0;
}
