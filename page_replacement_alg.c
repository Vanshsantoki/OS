#include <stdio.h>
#define max 100

void fifo(int pages[], int n, int f);
void lru(int pages[], int n, int f);
void optimal(int pages[], int n, int f);
int findOptimal(int pages[], int n, int index, int frames[], int f);

int main() {
    int pages[max], n, f;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);
    printf("\n--- FIFO ---\n");
    fifo(pages, n, f);
    printf("\n--- LRU ---\n");
    lru(pages, n, f); 
    printf("\n--- Optimal ---\n");
    optimal(pages, n, f);
    return 0;
}
// FIFO Algorithm
void fifo(int pages[], int n, int f) {
    int frames[f], idx = 0, faults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++)
            if (frames[j] == pages[i]) found = 1;
        if (!found) {
            frames[idx] = pages[i];
            idx = (idx + 1) % f;
            faults++;
        }
        printf("Page %d => ", pages[i]);
        for (int j = 0; j < f; j++)
            frames[j] != -1 ? printf("%d ", frames[j]) : printf("- ");
        printf("\n");
    }
    printf("Page faults: %d\n", faults);
}
// LRU Algorithm
void lru(int pages[], int n, int f) {
    int frames[f], time[f], faults = 0;

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                time[j] = i;
                found = 1;
                break;
            }
        }
        if (!found) {
            int lru = 0;
            for (int j = 1; j < f; j++)
                if (time[j] < time[lru]) lru = j;

            frames[lru] = pages[i];
            time[lru] = i;
            faults++;
        }
        printf("Page %d => ", pages[i]);
        for (int j = 0; j < f; j++)
            frames[j] != -1 ? printf("%d ", frames[j]) : printf("- ");
        printf("\n");
    }
    printf("Page faults: %d\n", faults);
}
// Optimal Algorithm
void optimal(int pages[], int n, int f) {
    int frames[f], faults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < f; j++)
            if (frames[j] == pages[i]) found = 1;

        if (!found) {
            int replace = findOptimal(pages, n, i, frames, f);
            frames[replace] = pages[i];
            faults++;
        }
        printf("Page %d => ", pages[i]);
        for (int j = 0; j < f; j++)
            frames[j] != -1 ? printf("%d ", frames[j]) : printf("- ");
        printf("\n");
    }
    printf("Page faults: %d\n", faults);
}
// Find index to replace for Optimal
int findOptimal(int pages[], int n, int index, int frames[], int f) {
    int farthest = index, pos = -1;

    for (int i = 0; i < f; i++) {
        int j;
        for (j = index + 1; j < n; j++)
            if (frames[i] == pages[j]) break;

        if (j == n) return i; // Not used again
        if (j > farthest) {
            farthest = j;
            pos = i;
        }
    }
    return pos == -1 ? 0 : pos;
}

